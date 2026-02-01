#ifndef ARGPARSE_H
#define ARGPARSE_H

#include <stdbool.h>
#include <stdlib.h>

typedef struct {
    char **data;
    size_t len;
} StringArray;

typedef struct {
    StringArray flags;
    StringArray arguments;
} Args;

Args *parser(StringArray *argv);
int string_array_includes(StringArray *str_arr, const char *val);

#endif
