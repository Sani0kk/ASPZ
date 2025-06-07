#include <stdio.h>
#include <time.h>
#include <limits.h>

int main() {
    printf("Розмір time_t: %zu байт\n", sizeof(time_t));
    
    if (sizeof(time_t) == 4) {
        printf("32-бітна архітектура:\n");
        time_t max_time = (time_t)INT_MAX;
        printf("Максимальне значення time_t: %ld\n", (long)max_time);
        printf("Дата закінчення: %s", ctime(&max_time));
    } else if (sizeof(time_t) == 8) {
        printf("64-бітна архітектура:\n");
        time_t max_time = (time_t)LONG_MAX;
        printf("Максимальне значення time_t: %ld\n", (long)max_time);
        printf("Дата закінчення: %s", ctime(&max_time));
    } else {
        printf("Невідома архітектура.\n");
    }

    return 0;
}
