#include <stdio.h>
#include "lwshell/lwshell.h"
#include <string.h>
#include <stdint.h>

/**
 * \brief           Reading one character at a time 
 *
 * This is useful to test the shell in a "raw" mode (non-canonical input)
 * Please note that conio.h is a windows only header
 */
#ifndef LWSHELL_TEST_READ_SINGLE_CHAR
#define LWSHELL_TEST_READ_SINGLE_CHAR 0
#endif

#if LWSHELL_TEST_READ_SINGLE_CHAR
#include <conio.h>
#endif

void example_minimal(void);

#if LWSHELL_CFG_USE_OUTPUT

/**
 * \brief           Application output function
 * \param[in]       str: String to print, null-terminated
 * \param[in]       lw: LwSHELL instance
 */
static void
shell_output(const char* str, lwshell_t* lw) {
    (void)lw;
    printf("%s", str);
    if (*str == '\r') {
        printf("\n");
    }
}

#endif /* LWSHELL_CFG_USE_OUTPUT */

/* Commands ... */

int32_t
addint_cmd(int32_t argc, char** argv) {
    long long i1, i2;
    if (argc < 3) {
        return -1;
    }
    i1 = lwshell_parse_long_long(argv[1]);
    i2 = lwshell_parse_long_long(argv[2]);

    printf("%lld\r\n", (i1 + i2));
    return 0;
}

int32_t
subint_cmd(int32_t argc, char** argv) {
    long long i1, i2;
    if (argc < 3) {
        return -1;
    }
    i1 = lwshell_parse_long_long(argv[1]);
    i2 = lwshell_parse_long_long(argv[2]);

    printf("%lld\r\n", (i1 - i2));
    return 0;
}

int32_t
adddbl_cmd(int32_t argc, char** argv) {
    double i1, i2;
    if (argc < 3) {
        return -1;
    }
    i1 = lwshell_parse_double(argv[1]);
    i2 = lwshell_parse_double(argv[2]);

    printf("%f\r\n", (i1 + i2));
    return 0;
}

int32_t
subdbl_cmd(int32_t argc, char** argv) {
    double i1, i2;
    if (argc < 3) {
        return -1;
    }
    i1 = lwshell_parse_double(argv[1]);
    i2 = lwshell_parse_double(argv[2]);

    printf("%f\r\n", (i1 - i2));
    return 0;
}

#if LWSHELL_CFG_USE_STATIC_COMMANDS

int32_t
addintstatic_cmd(int32_t argc, char** argv) {
    printf("Static command...\r\n");
    return addint_cmd(argc, argv);
}

int32_t
subintstatic_cmd(int32_t argc, char** argv) {
    printf("Static command...\r\n");
    return subint_cmd(argc, argv);
}

int32_t
adddblstatic_cmd(int32_t argc, char** argv) {
    printf("Static command...\r\n");
    return adddbl_cmd(argc, argv);
}

int32_t
subdblstatic_cmd(int32_t argc, char** argv) {
    printf("Static command...\r\n");
    return subdbl_cmd(argc, argv);
}

/*
 * Define some static commands, set as const.
 */
static const lwshell_cmd_t static_cmds[] = {
    {.name = "addintstatic", .desc = "Add 2 integers, a static implementation", .fn = addintstatic_cmd},
    {.name = "subintstatic", .desc = "Add 2 integers, a static implementation", .fn = subintstatic_cmd},
    {.name = "adddblstatic", .desc = "Add 2 integers, a static implementation", .fn = adddblstatic_cmd},
    {.name = "subdblstatic", .desc = "Add 2 integers, a static implementation", .fn = subdblstatic_cmd},
};

#endif /* LWSHELL_CFG_USE_STATIC_COMMANDS */

/* Program entry point */
int
main(void) {
    /* Init library */
    lwshell_init();

#if LWSHELL_CFG_USE_OUTPUT
    /* Add optional output function for the purpose of the feedback */
    lwshell_set_output_fn(shell_output);
#endif /* LWSHELL_CFG_USE_OUTPUT */

#if LWSHELL_CFG_USE_DYNAMIC_COMMANDS
    /* Define shell commands */
    lwshell_register_cmd("addint", addint_cmd, "Adds 2 integer numbers and prints them");
    lwshell_register_cmd("subint", subint_cmd, "Substitute 2 integer numbers and prints them");
    lwshell_register_cmd("adddbl", adddbl_cmd, "Adds 2 double numbers and prints them");
    lwshell_register_cmd("subdbl", subdbl_cmd, "Substitute 2 double numbers and prints them");
#endif /* LWSHELL_CFG_USE_DYNAMIC_COMMANDS */

#if LWSHELL_CFG_USE_STATIC_COMMANDS
    /* Register static commands -> one-time call for all commands */
    lwshell_register_static_cmds(static_cmds, LWSHELL_ARRAYSIZE(static_cmds));
#endif /* LWSHELL_CFG_USE_STATIC_COMMANDS */

    /* User input to process every character */
    printf("Start entering your command and press enter...\r\n");
    while (1) {
        char str[255];

#if LWSHELL_TEST_READ_SINGLE_CHAR
        str[0] = getch();
        str[1] = '\0';
#else
        fgets(str, sizeof(str), stdin);
#endif

        /* Insert input to library */
        lwshell_input(str, strlen(str));
    }
    return 0;
}
