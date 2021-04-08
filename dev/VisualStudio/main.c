#include <stdio.h>
#include "lwshell/lwshell.h"
#include <string.h>
#include <stdint.h>

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

int
main(int argc, char** argv) {
    printf("Program started...\r\n");
    printf("ARGC: %d\r\n", argc);
    for (size_t i = 0; i < argc; ++i) {
        printf("ARGV %d: %s\r\n", i, argv[i]);
    }
    printf("\r\n");

    lwshell_init();
    lwshell_register_cmd("addint", addint_cmd, "Adds 2 integer numbers and prints them");
    lwshell_register_cmd("subint", subint_cmd, "Substitute 2 integer numbers and prints them");
    lwshell_register_cmd("adddbl", adddbl_cmd, "Adds 2 double numbers and prints them");
    lwshell_register_cmd("subdbl", subdbl_cmd, "Substitute 2 double numbers and prints them");

    /* User input to process every character */
    printf("Start entering your text and press enter...\r\n");
    while (1) {
        char c = getch();
        if (c == '\b') {
            printf("\b \b");
        } else {
            printf("%c", c);
        }
        if (c == '\r') {
            printf("\n");
        }

        /* Now insert input */
        lwshell_input(&c, 1);
    }
    return 0;
}
