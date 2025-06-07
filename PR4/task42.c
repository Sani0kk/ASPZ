#include <stdio.h>
#include <stdlib.h>

int main() {
    int xa = 100000;
    int xb = 100000;
    int num = xa * xb; // потенційне переповнення

    printf("num = %d\n", num);

    void* ptr = malloc(num);
    if (ptr == NULL) {
        printf("malloc failed\n");
    } else {
        printf("malloc succeeded\n");
        free(ptr);
    }
    return 0;
}
