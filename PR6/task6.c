#include <stdlib.h>
#include <stdio.h>

int main() {
    int *array = malloc(5 * sizeof(int)); 

    array[0] = 42;
    printf("Value: %d\n", array[0]);
    return 0;
}
