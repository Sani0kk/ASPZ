#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <sys/resource.h>

int main() {
    FILE *file = fopen("dice_rolls.txt", "w");
    if (file == NULL) {
        printf("Помилка відкриття файлу\n");
        return 1;
    }
    struct rlimit rl;
    getrlimit(RLIMIT_FSIZE, &rl);
    rl.rlim_cur = 1024; // Ліміт 1 КБ
    setrlimit(RLIMIT_FSIZE, &rl);
    srand(time(NULL));
    for (int i = 0; i < 100; i++) {
        int roll = (rand() % 6) + 1;
        if (fprintf(file, "Кидок %d: %d\n", i + 1, roll) < 0) {
            printf("Перевищено ліміт розміру файлу\n");
            break;
        }
    }
    fclose(file);
    return 0;
}
