#include <stdio.h>
#include <stdlib.h>

int main() {
    FILE *fp = popen("rwho | more", "r");
    if (fp == NULL) {
        perror("Помилка виконання команди");
        exit(EXIT_FAILURE);
    }

    char buffer[256];
    while (fgets(buffer, sizeof(buffer), fp) != NULL) {
        printf("%s", buffer);
    }

    pclose(fp);
    return 0;
}
