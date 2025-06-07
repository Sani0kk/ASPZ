#include <stdio.h>
#include <stdlib.h>

int main() {
    void *ptr = NULL;
    for (int i = 0; i < 5; i++) {
        if (!ptr)
            ptr = malloc(1024);
        printf("Using ptr in iteration %d\n", i);
        free(ptr); // помилка: після free треба ptr = NULL
    }
    return 0;
}
