#include <stdio.h>
#include <time.h>
#include <limits.h>

int main() {
    printf("Розмір time_t: %zu байт\n", sizeof(time_t));
    if (sizeof(time_t) == 4) {
        printf("Максимальне значення time_t (32-біт): %ld\n", (long)INT_MAX);
        printf("Дата закінчення: 19 січня 2038 року, 03:14:07 UTC\n");
    } else if (sizeof(time_t) == 8) {
        printf("Максимальне значення time_t (64-біт): %lld\n", (long long)LLONG_MAX);
        printf("Дата закінчення: дуже далеко в майбутньому\n");
    }
    return 0;
}
