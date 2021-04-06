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
 * Version:         $_version_$
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
 * \brief           Enables `1` or disables `0` operating system support in the library
 *
 * \note            When `LWSHELL_CFG_OS` is enabled, user must implement functions in \ref LWSHELL_SYS group.
 */
#ifndef LWSHELL_CFG_OS
#define LWSHELL_CFG_OS                            0
#endif

/**
 * \brief           Mutex handle type
 *
 * \note            This value must be set in case \ref LWSHELL_CFG_OS is set to `1`.
 *                  If data type is not known to compiler, include header file with
 *                  definition before you define handle type
 */
#ifndef LWSHELL_CFG_OS_MUTEX_HANDLE
#define LWSHELL_CFG_OS_MUTEX_HANDLE               void *
#endif

/**
 * \brief           Number of bits to align memory address and memory size
 *
 * Some CPUs do not offer unaligned memory access (Cortex-M0 as an example)
 * therefore it is important to have alignment of data addresses and potentialy length of data
 *
 * \note            This value must be a power of `2` for number of bytes.
 *                  Usually alignment of `4` bytes fits to all processors.
 */
#ifndef LWSHELL_CFG_ALIGN_NUM
#define LWSHELL_CFG_ALIGN_NUM                     ((size_t)4)
#endif

/**
 * \brief           Enables `1` or disables `0` memory cleanup on free operation (or realloc).
 *
 * It resets unused memory to `0x00` and prevents other applications seeing old data.
 * It is disabled by default since it has performance penalties.
 * /
#ifndef LWSHELL_CFG_CLEAN_MEMORY
#define LWSHELL_CFG_CLEAN_MEMORY                  0
#endif

/**
 * \brief           Enables `1` or disables `0` statistics in the library
 *
 */
#ifndef LWSHELL_CFG_ENABLE_STATS
#define LWSHELL_CFG_ENABLE_STATS                  0
#endif

/**
 * \}
 */

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* LWSHELL_HDR_OPT_H */
