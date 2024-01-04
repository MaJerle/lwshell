/**
 * \file            lwshell.h
 * \brief           Lightweight shell
 */

/*
 * Copyright (c) 2024 Tilen MAJERLE
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
 * Version:         v1.2.0
 */
#ifndef LWSHELL_HDR_H
#define LWSHELL_HDR_H

#include <stdint.h>
#include <stdlib.h>
#include "lwshell/lwshell_opt.h"

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

/**
 * \defgroup        LWSHELL Lightweight shell
 * \brief           Lightweight shell
 * \{
 */

/**
 * \brief           Get size of statically allocated array
 * \param[in]       x: Object to get array size of
 * \return          Number of elements in array
 */
#define LWSHELL_ARRAYSIZE(x) (sizeof(x) / sizeof((x)[0]))

/**
 * \brief           LwSHELL result enumeration
 */
typedef enum {
    lwshellOK = 0x00, /*!< Everything OK */
    lwshellERRPAR,    /*!< Parameter error */
    lwshellERRMEM,    /*!< Memory error */
} lwshellr_t;

/* Forward declaration */
struct lwshell;

/**
 * \brief           Command function prototype
 * \param[in]       argc: Number of arguments
 * \param[in]       argv: Pointer to arguments
 * \return          `0` on success, `-1` otherwise
 */
typedef int32_t (*lwshell_cmd_fn)(int32_t argc, char** argv);

/**
 * \brief           Callback function for character output
 * \param[in]       str: String to output
 * \param[in]       lwobj: LwSHELL instance
 */
typedef void (*lwshell_output_fn)(const char* str, struct lwshell* lwobj);

/**
 * \brief           Shell command structure
 */
typedef struct {
    lwshell_cmd_fn fn; /*!< Command function to call on match */
    const char* name;  /*!< Command name to search for match */
    const char* desc;  /*!< Command description for help */
} lwshell_cmd_t;

/**
 * \brief           LwSHELL main structure
 */
typedef struct lwshell {
#if LWSHELL_CFG_USE_OUTPUT || __DOXYGEN__
    lwshell_output_fn out_fn;                 /*!< Optional output function */
#endif                                        /* LWSHELL_CFG_USE_OUTPUT || __DOXYGEN__ */
    char buff[LWSHELL_CFG_MAX_INPUT_LEN + 1]; /*!< Shell command input buffer */
    size_t buff_ptr;                          /*!< Buffer pointer for input */
    int32_t argc;                             /*!< Number of arguments parsed in command */
    char* argv[LWSHELL_CFG_MAX_CMD_ARGS];     /*!< Array of pointers to all arguments */

#if LWSHELL_CFG_USE_DYNAMIC_COMMANDS || __DOXYGEN__
    lwshell_cmd_t dynamic_cmds[LWSHELL_CFG_MAX_DYNAMIC_CMDS]; /*!< Shell registered dynamic commands */
    size_t dynamic_cmds_cnt;                                  /*!< Number of registered dynamic commands */
#endif                                                        /* LWSHELL_CFG_USE_DYNAMIC_COMMANDS || __DOXYGEN__ */

#if LWSHELL_CFG_USE_STATIC_COMMANDS || __DOXYGEN__
    const lwshell_cmd_t* static_cmds; /*!< Pointer to an array of static commands */
    size_t static_cmds_cnt;           /*!< Length of status commands array */
#endif                                /* LWSHELL_CFG_USE_STATIC_COMMANDS || __DOXYGEN__ */
} lwshell_t;

lwshellr_t lwshell_init_ex(lwshell_t* lwobj);
lwshellr_t lwshell_set_output_fn_ex(lwshell_t* lwobj, lwshell_output_fn out_fn);
lwshellr_t lwshell_register_cmd_ex(lwshell_t* lwobj, const char* cmd_name, lwshell_cmd_fn cmd_fn, const char* desc);
lwshellr_t lwshell_input_ex(lwshell_t* lwobj, const void* in_data, size_t len);

lwshellr_t lwshell_register_static_cmds_ex(lwshell_t* lwobj, const lwshell_cmd_t* cmds, size_t cmds_len);

/**
 * \brief           Initialize shell interface
 * \note            It applies to default shell instance
 * \return          \ref lwshellOK on success, member of \ref lwshellr_t otherwise
 */
#define lwshell_init()                               lwshell_init_ex(NULL)

/**
 * \brief           Set output function to use to print data from library to user
 * \note            It applies to default shell instance
 * \param[in]       out_fn: Output function to print library data.
 *                      Set to `NULL` to disable the feature
 * \return          \ref lwshellOK on success, member of \ref lwshellr_t otherwise
 */
#define lwshell_set_output_fn(out_fn)                lwshell_set_output_fn_ex(NULL, (out_fn))

/**
 * \brief           Register new command to shell
 * \note            It applies to default shell instance
 * \param[in]       cmd_name: Command name. This one is used when entering shell command
 * \param[in]       cmd_fn: Function to call on command match
 * \param[in]       desc: Custom command description
 * \return          \ref lwshellOK on success, member of \ref lwshellr_t otherwise
 * \note            Available only when \ref LWSHELL_CFG_USE_DYNAMIC_COMMANDS is enabled
 */
#define lwshell_register_cmd(cmd_name, cmd_fn, desc) lwshell_register_cmd_ex(NULL, (cmd_name), (cmd_fn), (desc))

/**
 * \brief           Input data to shell processing
 * \note            It applies to default shell instance
 * \param[in]       in_data: Input data to process
 * \param[in]       len: Length of data for input
 * \return          \ref lwshellOK on success, member of \ref lwshellr_t otherwise
 */
#define lwshell_input(in_data, len)                  lwshell_input_ex(NULL, (in_data), (len))

/**
 * \brief           Register new command to shell
 * \note            It applies to default shell instance
 * \param[in]       cmds: Array of const static commands. It can be from non-volatile memory
 * \param[in]       cmds_len: Length of array elements
 * \return          \ref lwshellOK on success, member of \ref lwshellr_t otherwise
 * \note            Available only when \ref LWSHELL_CFG_USE_STATIC_COMMANDS is enabled
 */
#define lwshell_register_static_cmds(cmds, cmds_len) lwshell_register_static_cmds_ex(NULL, (cmds), (cmds_len))

/**
 * \brief           Parse input string as `integer`
 * \param[in]       str: String to parse
 * \return          String parsed as integer
 */
#define lwshell_parse_int(str)                       atoi(str)

/**
 * \brief           Parse input string as `double`
 * \param[in]       str: String to parse
 * \return          String parsed as `double`
 */
#define lwshell_parse_double(str)                    atof(str)

/**
 * \brief           Parse input string as `long`
 * \param[in]       str: String to parse
 * \return          String parsed as `long`
 */
#define lwshell_parse_long(str)                      atol(str)

/**
 * \brief           Parse input string as `long long`
 * \param[in]       str: String to parse
 * \return          String parsed as `long long`
 */
#define lwshell_parse_long_long(str)                 atoll(str)

/**
 * \}
 */

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* LWSHELL_HDR_H */
