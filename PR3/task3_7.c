#include <stdio.h>
#include <stdlib.h>
#include <sys/resource.h>

int main() {
    struct rlimit rl;
    getrlimit(RLIMIT_AS, &rl);
    rl.rlim_cur = 1024 * 1024; // Ліміт 1 МБ
    setrlimit(RLIMIT_AS, &rl);
    char *data = malloc(1024 * 1024 * 2); // 2 МБ
    if (data == NULL) {
        printf("Перевищено ліміт віртуальної пам’яті\n");
    } else {
        printf("Пам’ять виділена\n");
        free(data);
    }
    return 0;
}
