#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <sys/resource.h>

int main() {
    struct rlimit rl;
    getrlimit(RLIMIT_CPU, &rl);
    rl.rlim_cur = 1; // Ліміт 1 секунда
    setrlimit(RLIMIT_CPU, &rl);
    srand(time(NULL));
    int nums49[7], nums36[6];
    for (int i = 0; i < 7; i++) {
        nums49[i] = (rand() % 49) + 1;
        for (int j = 0; j < i; j++) if (nums49[i] == nums49[j]) i--;
    }
    for (int i = 0; i < 6; i++) {
        nums36[i] = (rand() % 36) + 1;
        for (int j = 0; j < i; j++) if (nums36[i] == nums36[j]) i--;
    }
    printf("Лотерея: 7 з 49: ");
    for (int i = 0; i < 7; i++) printf("%d ", nums49[i]);
    printf("\n6 з 36: ");
    for (int i = 0; i < 6; i++) printf("%d ", nums36[i]);
    printf("\n");
    return 0;
}
