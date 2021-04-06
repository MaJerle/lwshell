/**
 * \file            lwshell.h
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
#ifndef LWSHELL_HDR_H
#define LWSHELL_HDR_H

#include <stdint.h>
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
#define LWSHELL_ARRAYSIZE(x)            (sizeof(x) / sizeof((x)[0]))

/**
 * \brief           LwSHELL result enumeration
 */
typedef enum {
    lwshellOK = 0x00,                           /*!< Everything OK */
} lwshellr_t;

/**
 *
 */
typedef int32_t(*lwshell_cmd_fn)(int32_t argc, const char** argv);

/**
 * \brief           LwSHELL main structure
 */
typedef struct lwshell {
    uint8_t res;
} lwshell_t;

/**
 * \}
 */

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* LWSHELL_HDR_H */
