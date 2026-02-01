#include <stdio.h>
#include <stdint.h>

#define _CRT_SECURE_NO_WARNINGS

void readFile(const char *path);

int main(int argc, char **argv) {
    if (argc < 2) {
        fprintf(stderr, "Usage: %s <file>\n", argv[0]);
        return 1;
    }

    readFile(argv[1]);

    return 0;
}

void readFile(const char *path) {
    FILE *fp;
    char s[1024];
    int lineCount = 0;

    fp = fopen(path, "r");
    if (!fp) {
        perror("fopen");
        return;
    }

    printf("%s\n", path);
    while ((fgets(s, sizeof s, fp)) != NULL)
        fprintf(stdout, "%-15d | %s", ++lineCount, s);

    fclose(fp);
}
