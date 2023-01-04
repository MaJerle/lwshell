#include <string.h>
#include "lwshell/lwshell.h"

/* Command to get called */
int32_t
mycmd_fn(int32_t argc, char** argv) {
    printf("mycmd_fn called. Number of argv: %d\r\n", (int)argc);
    for (int32_t i = 0; i < argc; ++i) {
        printf("ARG[%d]: %s\r\n", (int)i, argv[i]);
    }

    /* Successful execution */
    return 0;
}

/* Example code */
void
example_minimal(void) {
    const char* input_str = "mycmd param1 \"param 2 with space\"";

    /* Init library */
    lwshell_init();

    /* Define shell commands */
    lwshell_register_cmd("mycmd", mycmd_fn, "Adds 2 integer numbers and prints them");

    /* User input to process every character */

    /* Now insert input */
    lwshell_input(input_str, strlen(input_str));
}