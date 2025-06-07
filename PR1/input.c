#include <stdio.h>
#include "input.h"

int get_input() {
    int value;
    printf("Введіть число: ");
    scanf("%d", &value);
    return value;
}
