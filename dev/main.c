#include <stdio.h>
#include "lwshell/lwshell.h"
#include <string.h>
#include <stdint.h>

void    example_minimal(void);

int32_t
addint_cmd(int32_t argc, char** argv) {
    long long i1, i2;
    if (argc < 3) {
        return -1;
    }
    i1 = lwshell_parse_long_long(argv[1]);
    i2 = lwshell_parse_long_long(argv[2]);

    printf("%lld\r\n", i1 + i2);
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

    printf("%lld\r\n", i1 - i2);
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

/**
 * \brief           Application output function
 * \param[in]       str: String to print, null-terminated
 * \param[in]       lw: LwSHELL instance
 */
void
shell_output(const char* str, lwshell_t* lw) {
    printf("%s", str);
    if (*str == '\r') {
        printf("\n");
    }
}

/* Program entry point */
int
main(void) {
    /* Init library */
    lwshell_init();

    /* Add optional output function for the purpose of the feedback */
    lwshell_set_output_fn(shell_output);

    /* Define shell commands */
    lwshell_register_cmd("addint", addint_cmd, "Adds 2 integer numbers and prints them");
    lwshell_register_cmd("subint", subint_cmd, "Substitute 2 integer numbers and prints them");
    lwshell_register_cmd("adddbl", adddbl_cmd, "Adds 2 double numbers and prints them");
    lwshell_register_cmd("subdbl", subdbl_cmd, "Substitute 2 double numbers and prints them");

    /* User input to process every character */
    printf("Start entering your command and press enter...\r\n");
    while (1) {
        char str[255];
        fgets(str, sizeof(str), stdin);

        /* Insert input to library */
        lwshell_input(str, strlen(str));
    }
    return 0;
}
