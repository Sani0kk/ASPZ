#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

int main() {
    FILE *pipe = popen("getent passwd", "r");
    if (pipe == NULL) {
        perror("Помилка виконання popen");
        exit(EXIT_FAILURE);
    }

    char line[256];
    int current_uid = getuid();
    int normal_users = 0;

    while (fgets(line, sizeof(line), pipe) != NULL) {
        int uid;
        if (sscanf(line, "%*[^:]:%*[^:]:%d", &uid) == 1 && uid > 1000 && uid != current_uid) {
            normal_users++;
            printf("Знайдено користувача з UID: %d\n", uid);
        }
    }

    pclose(pipe);
    printf("Кількість звичайних користувачів (крім вас): %d\n", normal_users);
    return 0;
}
