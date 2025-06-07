#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>

struct sbar { int x[10]; };

int main() {
    struct sbar *ptr, *newptr;
    ptr = calloc(1000, sizeof(struct sbar));
    if (!ptr) return 1;

    newptr = reallocarray(ptr, 500, sizeof(struct sbar));
    if (newptr) {
        printf("reallocarray succeeded\n");
        free(newptr);
    } else {
        printf("reallocarray failed\n");
        free(ptr);
    }
    return 0;
}
