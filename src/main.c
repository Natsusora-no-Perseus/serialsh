#include <stdio.h>
#include <string.h>
#include "serialsh.h"

#define MAX_INPUT_SIZE 1024

int echo_back (char *args) {
    if (args == NULL) {
        printf("args is NULL\n");
        return 1;
    }
    printf("%s\n", args);
    return 0;
}

int echo_args (char *args) {
    if (args == NULL) {
        printf("args is NULL\n");
        return 1;
    }
    printf("Parsing: %s\n", args);
    char *params = strtok(args, " ");
    while (params != NULL)
    {
        if (params[0] == '-') {
            printf("\nOption %s: ", params);
        } else {
            printf("arg %s; ", params);
        }
        params = strtok(NULL, " ");
    }
    return 0;
}

int proc_wrap(const char **params) {
    int param = atoi(params[0]);
    printf("prov_wrap called with param %d\n", param);
    return 0;
}

int proc_level(const char **params) {
    int param = atoi(params[0]);
    printf("proc_level called with param %d\n", param);
    return 0;
}

int proc_state(const char **params) {
    int param1 = atoi(params[0]);
    int param2 = atoi(params[1]);
    printf("proc_state called with params %d, %d\n", param1, param2);
    return 0;
}

int proc_help(const char **params) {
    (void) params; // Do nothing; prevent -Wunused-variable
    printf("Dummy help message\n");
    return 0;
}

SrshArgEntry apt_specs[] = {
    {'w', 1, proc_wrap},
    {'l', 1, proc_level},
    {'s', 2, proc_state},
    {'h', 0, proc_help}
};

int argparse_test (char *args) {
    int ret = srsh_proc_args(args, apt_specs,
                             sizeof(apt_specs) / sizeof(apt_specs[0]));
    return ret;
}

int main() {
    char input_b[MAX_INPUT_SIZE];
    char echo_back_name[] = "echo";
    char echo_args_name[] = "eargs";
    char proc_args_name[] = "pargs";
    int call_ret = 0;

    printf("SerialSh dummy ready.\n");

    srsh_register_func((void *)echo_back, echo_back_name, NULL);
    srsh_register_func((void *)echo_args, echo_args_name, NULL);
    srsh_register_func((void *)argparse_test, proc_args_name, apt_specs);

    while(1) {
        printf("> ");

        if (fgets(input_b, sizeof(input_b), stdin) == NULL) {
            printf("Error reading input.\n");
            continue;
        } else {
            // Remove the trailing '\n' in input
            input_b[strcspn(input_b, "\n")] = 0;
        }

        if (strcmp(input_b, "exit") == 0) {
            printf("Exiting...\n");
            break;
        }

        call_ret = srsh_parse(input_b);
        printf("Parse result: %d\n", call_ret);
    }

    return 0;
}
