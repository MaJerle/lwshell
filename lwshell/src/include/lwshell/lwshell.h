/**
 * \file            lwshell.h
 * \brief           Lightweight shell
 */

/*
 * Copyright (c) 2022 Tilen MAJERLE
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
 * Version:         v1.1.1
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
 * \param[in]       lw: LwSHELL instance
 */
typedef void (*lwshell_output_fn)(const char* str, struct lwshell* lw);

/**
 * \brief           LwSHELL main structure
 */
typedef struct lwshell {
    lwshell_output_fn out_fn;                 /*!< Optional output function */
    char buff[LWSHELL_CFG_MAX_INPUT_LEN + 1]; /*!< Shell command input buffer */
    size_t buff_ptr;                          /*!< Buffer pointer for input */
    int32_t argc;                             /*!< Number of arguments parsed in command */
    char* argv[LWSHELL_CFG_MAX_CMD_ARGS];     /*!< Array of all arguments */
} lwshell_t;

/**
 * \brief           Shell command structure
 */
typedef struct {
    lwshell_cmd_fn fn; /*!< Command function to call on match */
    const char* name;  /*!< Command name to search for match */
    const char* desc;  /*!< Command description for help */
} lwshell_cmd_t;

lwshellr_t lwshell_init(void);
lwshellr_t lwshell_set_output_fn(lwshell_output_fn out_fn);
lwshellr_t lwshell_register_cmd(const char* cmd_name, lwshell_cmd_fn cmd_fn, const char* desc);
lwshellr_t lwshell_input(const void* in_data, size_t len);

/**
 * \brief           Parse input string as `integer`
 * \param[in]       str: String to parse
 * \return          String parsed as integer
 */
#define lwshell_parse_int(str)       atoi(str)

/**
 * \brief           Parse input string as `double`
 * \param[in]       str: String to parse
 * \return          String parsed as `double`
 */
#define lwshell_parse_double(str)    atof(str)

/**
 * \brief           Parse input string as `long`
 * \param[in]       str: String to parse
 * \return          String parsed as `long`
 */
#define lwshell_parse_long(str)      atol(str)

/**
 * \brief           Parse input string as `long long`
 * \param[in]       str: String to parse
 * \return          String parsed as `long long`
 */
#define lwshell_parse_long_long(str) atoll(str)

/**
 * \}
 */

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* LWSHELL_HDR_H */
