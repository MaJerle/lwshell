#include <stdio.h>
#include "lwshell/lwshell.h"
#include <string.h>
#include <stdint.h>

int32_t
addint_cmd(int32_t argc, char** argv) {
    printf("ADDINT CMD, args: %d\r\n", argc);
    for (size_t i = 0; i < argc; ++i) {
        printf("Arg %d: %s\r\n", (int)i, argv[i]);
    }
    return 0;
}

int
main(void) {
    lwshell_init();
    lwshell_register_cmd("addint", addint_cmd, "Adds int between 2 arguments");

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
