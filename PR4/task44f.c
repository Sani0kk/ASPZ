#include <stdio.h>
#include <stdlib.h>

int main() {
    void *ptr = NULL;
    for (int i = 0; i < 5; i++) {
        ptr = malloc(1024);
        if (!ptr) {
            printf("Allocation failed\n");
            break;
        }
        printf("Using ptr in iteration %d\n", i);
        free(ptr);
    }
    return 0;
}
