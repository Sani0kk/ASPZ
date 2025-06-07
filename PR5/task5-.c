#include <stdio.h>

int main() {
    int x = 12345;

    // Помилково використали x як покажчик
    int value = * (int *) x;

    printf("Value = %d\n", value);
    return 0;
}
