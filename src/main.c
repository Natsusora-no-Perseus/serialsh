#include <stdio.h>
#include <string.h>
#include "Serialsh.h"

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

int main() {
    char input_b[MAX_INPUT_SIZE];
    char echo_back_name[] = "echo";
    char echo_args_name[] = "eargs";
    int call_ret = 0;

    printf("SerialSh dummy ready.\n");

    srsh_register_func((void *)echo_back, echo_back_name);
    srsh_register_func((void *)echo_args, echo_args_name);

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

        call_ret = srsh_parse(input_b, 0);
        printf("Parse result: %d\n", call_ret);
    }

    return 0;
}
