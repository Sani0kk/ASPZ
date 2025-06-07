#include <stdio.h>

int main() {
    int x = 12345;
    int *ptr = &x;

    int value = *ptr;

    printf("Correct value = %d\n", value);
    return 0;
}
