#include <stdio.h>
#include <stdlib.h>

int main() {
    char *ptr = malloc(1024);
    if (!ptr) return 1;

    char *newptr = realloc(ptr, (size_t)-1); // дуже великий розмір
    if (!newptr) {
        printf("realloc failed, original pointer not freed\n");
        free(ptr);
    } else {
        printf("realloc succeeded\n");
        free(newptr);
    }
    return 0;
}
