#include <stdio.h>
#include "lwshell/lwshell.h"

typedef struct {
    const char* command;
    const char* args_list[16];
} test_str_t;

/* List of commands */
static const test_str_t commands[] = {
    {
        .command = "test 123 456 789\n",
        .args_list =
        {
            "test",
            "123",
            "456",
            "789",
        },
    },
    {
        .command = "test 123 longer text\n",
        .args_list =
        {
            "test",
            "123",
            "longer",
            "text",
        },
    },
    {
        .command = "test 123 \"longer text\"\n",
        .args_list =
        {
            "test",
            "123",
            "longer text",
        },
    },
    {
        .command = "test 123 \"longer text with \\\" quotes\"\n",
        .args_list =
        {
            "test",
            "123",
            "longer text with \\\" quotes",
        },
    },
};
static uint32_t current_cmd_index;
static int failed = 0;

/**
 * \brief           Test command function
 *
 * \param           argc
 * \param           argv
 * \return          int32_t
 */
int32_t
prv_test_cmd(int32_t argc, char** argv) {
    const test_str_t* cmd = &commands[current_cmd_index];
    int32_t cmd_args_count;

    /* Get list of arguments from test command */
    for (cmd_args_count = 0; cmd->args_list[cmd_args_count] != NULL; ++cmd_args_count) {}
    if (cmd_args_count != argc) {
        printf("Test failed: Expected argument count (%02u) does not match actual argument count (%02u)\r\n",
               (unsigned)cmd_args_count, (unsigned)argc);
        failed = 1;
        return -1;
    }

    /* Check if parameters match */
    for (int32_t idx = 0; idx < argc; ++idx) {
        /* Argument failed */
        if (strcmp(cmd->args_list[idx], argv[idx]) != 0) {
            printf("Test failed: Argument index %02u, value \"%s\" does not match actual argument value \"%s\"\r\n",
                   (unsigned)idx, cmd->args_list[idx], argv[idx]);
            failed = 1;
            return -1;
        }
    }

    return 0;
}

/**
 * \brief           Global test run function
 *
 */
int
run_test(void) {
    failed = 0;

    printf("Running test...\r\n");
    lwshell_init();
    lwshell_register_cmd("test", prv_test_cmd, "Test command function\r\n");

    /* Run all commands */
    for (current_cmd_index = 0; current_cmd_index < LWSHELL_ARRAYSIZE(commands); ++current_cmd_index) {
        lwshell_input(commands[current_cmd_index].command, strlen(commands[current_cmd_index].command));
    }
    printf("Tests completed...\r\n");
    return failed ? -1 : 0;
}
