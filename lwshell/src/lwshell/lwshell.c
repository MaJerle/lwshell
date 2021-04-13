/**
 * \file            lwshell.c
 * \brief           Lightweight shell
 */

/*
 * Copyright (c) 2020 Tilen MAJERLE
 *
 * Permission is hereby granted, free of charge, to any person
 * obtaining a copy of this software and associated documentation
 * files (the "Software"), to deal in the Software without restriction,
 * including without limitation the rights to use, copy, modify, merge,
 * publish, distribute, sublicense, and/or sell copies of the Software,
 * and to permit persons to whom the Software is furnished to do so,
 * subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be
 * included in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES
 * OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE
 * AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT
 * HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY,
 * WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 * FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
 * OTHER DEALINGS IN THE SOFTWARE.
 *
 * This file is part of LwSHELL - Lightweight shell library.
 *
 * Author:          Tilen MAJERLE <tilen@majerle.eu>
 * Version:         $_version_$
 */
#include <string.h>
#include "lwshell/lwshell.h"

/* Default characters */
#define LWSHELL_ASCII_NULL                      0x00    /*!< Null character */
#define LWSHELL_ASCII_BACKSPACE                 0x08    /*!< Backspace */
#define LWSHELL_ASCII_LF                        0x0A    /*!< Line feed */
#define LWSHELL_ASCII_CR                        0x0D    /*!< Carriage return */
#define LWSHELL_ASCII_DEL                       0x7F    /*!< Delete character */
#define LWSHELL_ASCII_SPACE                     0x20    /*!< Space character */

#if LWSHELL_CFG_USE_OUTPUT
#define LW_OUTPUT(lw, str)          do { if ((lw)->out_fn != NULL && (str) != NULL) { (lw)->out_fn((str), (lw)); }} while (0)
#else
#define LW_OUTPUT(lw, str)
#endif

/**
 * \brief           Shell command structure
 */
typedef struct {
    lwshell_cmd_fn fn;                          /*!< Command function to call on match */
    const char* name;                           /*!< Command name to search for match */
    const char* desc;                           /*!< Command description for help */
} lwshell_cmd_t;

/* Array of all commands */
static lwshell_cmd_t cmds[LWSHELL_CFG_MAX_CMDS];
static size_t cmds_cnt;
static lwshell_t shell;

/* Get shell instance from input */
#define LWSHELL_GET_LW(lw)          ((lw) != NULL ? (lw) : (&shell))

 /* Add character to instance */
#define LWSHELL_ADD_CH(lw, ch)      do {            \
    if ((lw)->buff_ptr < (LWSHELL_ARRAYSIZE(lw->buff) - 1)) {   \
        (lw)->buff[(lw)->buff_ptr] = ch;            \
        (lw)->buff[++(lw)->buff_ptr] = '\0';        \
    }                                               \
} while (0)

/* Reset buffers */
#define LWSHELL_RESET_BUFF(lw)      do {            \
    memset((lw)->buff, 0x00, sizeof((lw)->buff));   \
    memset((lw)->argv, 0x00, sizeof((lw)->argv));   \
    (lw)->buff_ptr = 0;                             \
} while (0)

/**
 * \brief           Parse input string
 * \param[in]       lw: LwSHELL instance
 */
static void
prv_parse_input(lwshell_t* lw) {
    size_t s_len;
    char ch, prev_ch;
    char* str;

    lw = LWSHELL_GET_LW(lw);

    /* Check string length and compare */
    s_len = strlen(lw->buff);
    if (lw->buff_ptr != s_len) {
        return;
    }

    /* Must be more than `1` character since we have to include end of line */
    if (lw->buff_ptr > 0) {
        uint8_t in_quote = 0;

        /* Set default values */
        lw->argc = 0;
        lw->argv[0] = lw->buff;

        /* Process complete input */
        prev_ch = '\0';
        str = lw->buff;
        
        /* Process complete string */
        lw->argc = 0;
        while (*str != '\0') {
            while (*str == ' ' && ++str) {}     /* Remove leading spaces */
            if (*str == '\0') {
                break;
            }

            /* Check if it starts with quote to handle escapes */
            if (*str == '"') {
                ++str;
                lw->argv[lw->argc++] = str;         /* Set start of argument after quotes */

                /* Process until end of quote */
                while (*str != '\0') {
                    if (*str == '\\') {
                        ++str;
                        if (*str == '"') {
                            ++str;
                        }
                    } else if (*str == '"') {
                        *str = '\0';
                        ++str;
                        break;
                    } else {
                        ++str;
                    }
                }
            } else {
                lw->argv[lw->argc++] = str;         /* Set start of argument directly on character */
                while ((*str != ' ' && *str != '\0')) {
                    if (*str == '"') {              /* Quote should not be here... */
                        *str = '\0';                /* ...add NULL termination to end token */
                    }
                    ++str;
                }
                *str = '\0';
                ++str;
            }

            /* Check for number of arguments */
            if (lw->argc == LWSHELL_ARRAYSIZE(lw->argv)) {
                break;
            }
        }

        /* Check for command */
        if (lw->argc > 0 && cmds_cnt > 0) {
            lwshell_cmd_t* c = NULL;
            /* Process all commands */
            for (size_t i = 0; i < cmds_cnt; ++i) {
                if (strncmp(cmds[i].name, lw->argv[0], strlen(lw->argv[0])) == 0) {
                    c = &cmds[i];
                    break;
                }
            }

            /* Valid command ready? */
            if (c != NULL) {
                if (lw->argc == 2
                    && lw->argv[1][0] == '-' && lw->argv[1][1] == 'h' && lw->argv[1][2] == '\0') {
                    /* Here we can print version */
                    LW_OUTPUT(lw, c->desc);
                    LW_OUTPUT(lw, "\r\n");
                } else {
                    c->fn(lw->argc, lw->argv);
                }
            }
        }
    }
}

/**
 * \brief           Initialize shell interface
 * \return          \ref lwshellOK on success, member of \ref lwshellr_t otherwise
 */
lwshellr_t
lwshell_init(void) {
    lwshell_t* lw = LWSHELL_GET_LW(NULL);
    memset(lw, 0x00, sizeof(*lw));
    return lwshellOK;
}

#if LWSHELL_CFG_USE_OUTPUT || __DOXYGEN__

/**
 * \brief           Set output function to use to print data from library to user
 * \param[in]       out_fn: Output function to print library data.
 *                      Set to `NULL` to disable the feature
 * \return          \ref lwshellOK on success, member of \ref lwshellr_t otherwise
 */
lwshellr_t
lwshell_set_output_fn(lwshell_output_fn out_fn) {
    lwshell_t* lw = LWSHELL_GET_LW(NULL);
    lw->out_fn = out_fn;
    return lwshellOK;
}

#endif /* LWSHELL_CFG_USE_OUTPUT || __DOXYGEN__ */

/**
 * \brief           Register new command to shell
 * \param[in]       cmd_name: Command name. This one is used when entering shell command
 * \param[in]       cmd_fn: Function to call on command match
 * \param[in]       desc: Custom command description
 * \return          \ref lwshellOK on success, member of \ref lwshellr_t otherwise
 */
lwshellr_t
lwshell_register_cmd(const char* cmd_name, lwshell_cmd_fn cmd_fn, const char* desc) {
    if (cmd_name == NULL || cmd_fn == NULL
        || strlen(cmd_name) == 0) {
        return lwshellERRPAR;
    }

    /* Check for memory available */
    if (cmds_cnt < LWSHELL_ARRAYSIZE(cmds)) {
        cmds[cmds_cnt].name = cmd_name;
        cmds[cmds_cnt].fn = cmd_fn;
        cmds[cmds_cnt].desc = desc;

        ++cmds_cnt;
        return lwshellOK;
    }
    return lwshellERRMEM;
}

/**
 * \brief           Input data to shell processing
 * \param[in]       in_data: Input data to process
 * \param[in]       len: Length of data for input
 * \return          \ref lwshellOK on success, member of \ref lwshellr_t otherwise
 */
lwshellr_t
lwshell_input(const void* in_data, size_t len) {
    const char* d = in_data;
    lwshell_t* lw = LWSHELL_GET_LW(NULL);

    if (in_data == NULL || len == 0) {
        return lwshellERRPAR;
    }

    /* Process all bytes */
    for (size_t i = 0; i < len; ++i) {
        switch (d[i]) {
            case LWSHELL_ASCII_CR: {
                LW_OUTPUT(lw, "\r");
                prv_parse_input(lw);
                LWSHELL_RESET_BUFF(lw);
                break;
            }
            case LWSHELL_ASCII_LF: {
                LW_OUTPUT(lw, "\n");
                prv_parse_input(lw);
                LWSHELL_RESET_BUFF(lw);
                break;
            }
            case LWSHELL_ASCII_BACKSPACE: {
                /* Try to delete character from buffer */
                if (lw->buff_ptr > 0) {
                    lw->buff[lw->buff_ptr] = '\0';
                    --lw->buff_ptr;
                    LW_OUTPUT(lw, "\b \b");
                }
                break;
            }
            default: {
                char str[2] = { d[i] };
                LW_OUTPUT(lw, str);
                if (d[i] >= 0x20 && d[i] < 0x7F) {
                    LWSHELL_ADD_CH(lw, d[i]);
                }
            }
        }
    }
    return lwshellOK;
}
