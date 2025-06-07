#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

int cmp(const void *a, const void *b) {
    return *(int*)a - *(int*)b;
}

void print_array(int *arr, int n) {
    for (int i = 0; i < n; i++) printf("%d ", arr[i]);
    printf("\n");
}

void test_array(int *arr, int n) {
    int *copy = malloc(n * sizeof(int));
    memcpy(copy, arr, n * sizeof(int));

    clock_t start = clock();
    qsort(copy, n, sizeof(int), cmp);
    clock_t end = clock();

    double elapsed = (double)(end - start) / CLOCKS_PER_SEC * 1000;
    printf("Time: %.3f ms\n", elapsed);
    free(copy);
}

int main() {
    int n = 100000;
    int *arr = malloc(n * sizeof(int));

    for (int i = 0; i < n; i++) arr[i] = i;
    printf("Сортований масив:\n");
    test_array(arr, n);

    for (int i = 0; i < n; i++) arr[i] = n - i;
    printf("Обернений масив:\n");
    test_array(arr, n);

    srand(time(NULL));
    for (int i = 0; i < n; i++) arr[i] = rand() % 1000;
    printf("Випадковий масив:\n");
    test_array(arr, n);

    free(arr);
    return 0;
}
