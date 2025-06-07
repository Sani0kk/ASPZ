#include <stdio.h>
#include <time.h>

int main() {
    clock_t start = clock();

    for (volatile int i = 0; i < 100000000; i++);

    clock_t end = clock();
    double elapsed_ms = ((double)(end - start)) / CLOCKS_PER_SEC * 1000.0;

    printf("Elapsed time: %.2f ms\n", elapsed_ms);
    return 0;
}
