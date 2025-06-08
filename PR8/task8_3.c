#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int compare(const void *a, const void *b) {
    return (*(int *)a - *(int *)b);
}

void test_qsort(int *arr, int size, const char *test_name) {
    int *copy = malloc(size * sizeof(int));
    for (int i = 0; i < size; i++) copy[i] = arr[i];
    clock_t start = clock();
    qsort(copy, size, sizeof(int), compare);
    clock_t end = clock();
    double time_spent = (double)(end - start) / CLOCKS_PER_SEC;
    printf("%s: Час виконання %.6f сек\n", test_name, time_spent);
    free(copy);
}

int main() {
    int size = 10000;
    int *arr = malloc(size * sizeof(int));

    // Тест 1: Відсортований масив
    for (int i = 0; i < size; i++) arr[i] = i;
    test_qsort(arr, size, "Відсортований");

    // Тест 2: Зворотньо відсортований масив
    for (int i = 0; i < size; i++) arr[i] = size - i;
    test_qsort(arr, size, "Зворотньо відсортований");

    // Перевірка правильності
    int test_arr[] = {5, 2, 9, 1, 5, 6};
    int expected[] = {1, 2, 5, 5, 6, 9};
    qsort(test_arr, 6, sizeof(int), compare);
    printf("Тест правильності: ");
    int passed = 1;
    for (int i = 0; i < 6; i++) {
        printf("%d ", test_arr[i]);
        if (test_arr[i] != expected[i]) passed = 0;
    }
    printf("(%s)\n", passed ? "Пройдено" : "Не пройдено");

    free(arr);
    return 0;
}
