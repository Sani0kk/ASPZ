#include <stdio.h>
#include <stdlib.h>

int main() {
    char *p1 = realloc(NULL, 1024); // еквівалент malloc
    if (p1) {
        printf("realloc(NULL, size) succeeded\n");
        free(p1);
    }

    char *p2 = malloc(1024);
    char *p3 = realloc(p2, 0); // має працювати як free
    if (!p3) {
        printf("realloc(p, 0) returned NULL (as expected)\n");
    }

    return 0;
}
