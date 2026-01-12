#include <stdio.h>
#include <stdbool.h>

int my_strlen(const char *s);
bool my_strcmp(const char *s1, const char *s2);

int main(int argc, char **argv) {
    if (argc < 3) {
        fprintf(stderr, "Usage: %s [OPTION] <str>\nOPTIONS:\n -l: get str's char count.", argv[0]);
        return 1;
    }

    if (my_strcmp(argv[1], "-l")) {
        fprintf(stdout, "%d\n", my_strlen(argv[2]));
    } else {
        fprintf(stderr, "Unknown argument");
        return 1;
    }

    return 0;
}

int my_strlen(const char *s) {
    const char *p = s;
    while (*p != '\0')
        p++;
    return p - s; // only use pointer subtraction between two pointers that point to the same array!
}

bool my_strcmp(const char *s1, const char *s2) {
    while (*s1 != '\0' && *s2 != '\0') {
        if (*s1 != *s2) {
            return false;
        }
        s1++;
        s2++;
    }

    return (*s1 == *s2);
}
