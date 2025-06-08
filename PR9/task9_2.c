#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main() {
    if (setuid(0) == -1) {
        fprintf(stderr, "Помилка: не вдалося отримати права root. Перевірте sudo.\n");
        exit(EXIT_FAILURE);
    }
    if (getuid() != 0) {
        fprintf(stderr, "Помилка: немає доступу до root.\n");
        exit(EXIT_FAILURE);
    }

    FILE *fp = popen("cat /etc/shadow", "r");
    if (fp == NULL) {
        perror("Помилка виконання popen");
        exit(EXIT_FAILURE);
    }

    char buffer[256];
    while (fgets(buffer, sizeof(buffer), fp) != NULL) {
        printf("%s", buffer);
    }

    pclose(fp);
    return 0;
}
