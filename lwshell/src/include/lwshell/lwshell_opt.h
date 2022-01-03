/**
 * \file            lwshell_opt.h
 * \brief           LwSHELL options
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
 * Version:         v1.1.1
 */
#ifndef LWSHELL_HDR_OPT_H
#define LWSHELL_HDR_OPT_H

/* Uncomment to ignore user options (or set macro in compiler flags) */
/* #define LWSHELL_IGNORE_USER_OPTS */

/* Include application options */
#ifndef LWSHELL_IGNORE_USER_OPTS
#include "lwshell_opts.h"
#endif /* LWSHELL_IGNORE_USER_OPTS */

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

/**
 * \defgroup        LWSHELL_OPT Configuration
 * \brief           LwSHELL options
 * \{
 */

/**
 * \brief           Maximum number of different commands to be registered
 *
 */
#ifndef LWSHELL_CFG_MAX_CMDS
#define LWSHELL_CFG_MAX_CMDS                    8
#endif

/**
 * \brief           Maximum characters for command line input
 *
 * This includes new line character and trailing zero.
 * Commands longer than this are automatically discarded
 */
#ifndef LWSHELL_CFG_MAX_INPUT_LEN
#define LWSHELL_CFG_MAX_INPUT_LEN               128
#endif

/**
 * \brief           Maximum characters for command name
 *
 */
#ifndef LWSHELL_CFG_MAX_CMD_NAME_LEN
#define LWSHELL_CFG_MAX_CMD_NAME_LEN            16
#endif

/**
 * \brief           Maximum number of parameters accepted by command.
 *
 * Number includes command name itself
 */
#ifndef LWSHELL_CFG_MAX_CMD_ARGS
#define LWSHELL_CFG_MAX_CMD_ARGS                8
#endif

/**
 * \brief           Enables `1` or disables `0` output function to
 *                  print data from library to application.
 *
 * This is useful to give library feedback to user
 */
#ifndef LWSHELL_CFG_USE_OUTPUT
#define LWSHELL_CFG_USE_OUTPUT                  1
#endif

/**
 * \brief           Enables `1` or disables `0` generic ˙listcmd` command to list of registered commands
 *
 * \ref LWSHELL_CFG_USE_OUTPUT must be enabled to use this feature
 */
#ifndef LWSHELL_CFG_USE_ENABLE_LIST_CMD
#define LWSHELL_CFG_USE_ENABLE_LIST_CMD         0
#endif

/**
 * \}
 */

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* LWSHELL_HDR_OPT_H */
