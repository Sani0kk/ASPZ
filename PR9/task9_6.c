#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main() {
    FILE *cmd = popen("whoami", "r");
    if (cmd == NULL) {
        perror("Помилка виконання whoami");
        exit(EXIT_FAILURE);
    }
    char name[256];
    fgets(name, sizeof(name), cmd);
    printf("whoami: %s", name);
    pclose(cmd);

    cmd = popen("id", "r");
    if (cmd == NULL) {
        perror("Помилка виконання id");
        exit(EXIT_FAILURE);
    }
    printf("id: ");
    char id_line[256];
    while (fgets(id_line, sizeof(id_line), cmd) != NULL) {
        printf("%s", id_line);
    }
    pclose(cmd);

    return 0;
}
