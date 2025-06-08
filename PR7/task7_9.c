#include <stdio.h>
#include <time.h>

int main() {
    clock_t start = clock();
    for (int i = 0; i < 1000000; i++) {
        // Імітація обчислень
    }
    clock_t end = clock();
    double time_spent = (double)(end - start) / CLOCKS_PER_SEC * 1000;
    printf("Час виконання: %.2f мс\n", time_spent);
    return 0;
}
