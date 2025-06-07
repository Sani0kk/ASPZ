#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <limits.h>

int main() {
    size_t max = SIZE_MAX;
    printf("SIZE_MAX = %zu bytes\n", max);

    void* ptr = malloc(max);
    if (ptr == NULL) {
        printf("malloc failed at max size\n");
    } else {
        printf("malloc succeeded\n");
        free(ptr);
    }
    return 0;
}
