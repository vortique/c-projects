#include <stdio.h>

void *my_memcpy(void *dest, void *src, int byte_count);

int main(void) {
    int a[5] = { 1, 2, 3, 4, 5 };
    int b[5];

    my_memcpy(b, a, sizeof b);

    int *p = &b[0];
    int *end = p + (sizeof b / sizeof b[0]);

    for (; p < end; p++) {
        printf("%d\n", *p);
    }

    return 0;
}

void *my_memcpy(void *dest, void *src, int byte_count) {
    char *s = src, *d = dest;

    while (byte_count--) {
        *d++ = *s++;
    }

    return dest;
}
