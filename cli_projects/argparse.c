#include "argparse.h"
#include <stdlib.h>
#include <stdbool.h>
#include <stddef.h>

Args *parser(StringArray *argv);
bool str_startswith(const char *str, const char *expr);
bool str_comp(const char *s1, const char *s2);
int str_length(const char *s);
char *str_includes(const char *str, const char *expr);
int string_array_includes(StringArray *str_arr, const char *val);

// EXAMPLE USAGE
// int main(int argc, char **argv) {
//     StringArray argv_string_array = { .data=argv, .len=argc };

//     Args *parsed_args = parser(&argv_string_array);
//
//     free(parsed_args);
// }

Args *parser(StringArray *args) {
    char **data = args->data;
    char **data_end = args->data + args->len;

    data++; // skip the file name

    StringArray flags = { .data=NULL, .len=0 };
    StringArray arguments = { .data=NULL, .len=0 };

    for (; data < data_end; data++) {
        if (str_startswith(*data, "-")) {
            // if the flags.data is NULL realloc behaves as malloc, no need to use malloc seperately :P
            char **tmp = flags.data = realloc(flags.data, (flags.len + 1) * sizeof(char *));
            if (!tmp)
                return NULL;
            flags.data = tmp;
            flags.data[flags.len] = *data;
            flags.len++;
            continue;
        }

        char **tmp = realloc(arguments.data, (arguments.len + 1) * sizeof(char *));
        if (!tmp)
            return NULL;
        arguments.data = tmp;
        arguments.data[arguments.len] = *data;
        arguments.len++;
    }

    Args *parsed_args = malloc(sizeof(Args));

    parsed_args->flags = flags;
    parsed_args->arguments = arguments;

    return parsed_args;
}

int string_array_includes(StringArray *str_arr, const char *val) {
    for (size_t i = 0; i < str_arr->len; i++) {
        if (str_comp(str_arr->data[i], val)) {
            return i;
        }
    }

    return -1;
}

char *str_includes(const char *str, const char *expr) {
    // NOT IMPLEMENTED
    return NULL;
}

bool str_startswith(const char *str, const char *expr) {
    if (expr == NULL || str_comp(str, "") || (str_length(str) < str_length(expr)))
        return false;

    while (*expr != '\0') {
        if (*str != *expr) {
            return false;
        }
        str++;
        expr++;
    }

    return true;
}

bool str_comp(const char *s1, const char *s2) {
    while (*s1 != '\0' && *s2 != '\0') {
        if (*s1 != *s2) {
            return false;
        }
        s1++;
        s2++;
    }

    return (*s1 == *s2);
}

int str_length(const char *s) {
    const char *p = s;
    while (*p != '\0')
        p++;
    return p - s;
}
