# serialsh
Yet another shell-like thing over a serial connection. (Will) have conditional support.

# Usage

For each function registered, you need to implement a function to process its arguments. Alternatively, a function `srsh_proc_args` has already been implemented to cover the most common use cases, and you would only need to implement functions to process each argument if you choose to use it.

Then you would need register these functions, and call `srsh_parse` every time you want to parse an input string.

## Example 
```
// Implement argument processors:
int foo_process_echo(const char **params) {
    int param = atoi(params[0]);
    printf("foo got parameter %d for argument -e.\n", param);
    return 0;
}

int foo_process_help(const char **param) {
    printf("This is a help message. Use argument -h to show it.\n");
    return 0;
}

// If you use srsh_proc_args:
int foo_arg_parser(char *args) {
    SrshArgEntry arg_lst[] = {
        // Argument; number of parameters; function to argument processor
        {'e', 1, foo_process_echo},
        {'h', 0, foo_process_help}
    }
    int ret = srsh_proc_args(args, arg_lst, sizeof(arg_lst)/sizeof(arg_lst[0]));
    return ret;
}

// Or if you want to implement the processor yourself:
int bar_arg_parser(char *args) {
    // Do something
    return 0;
}

// Finally register the functions:
const char foo_func_name[] = "foo";
srsh_register_func((void *) foo_arg_parser, foo_func_name);

// And call on an input string for parsing:
int parse_result = srsh_parse(input_buffer);
```
After implementing an input interface, it could work like this:
```
> foo -h
This is a help message. Use argument -h to show it.
> foo -e 42
foo got parameter %d for argument -e.
```
