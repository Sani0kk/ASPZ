#include <stdio.h>
#include <string.h>

int main(int argc, char *argv[]) {
    if (argc != 3) {
        printf("Використання: %s файл слово\n", argv[0]);
        return 1;
    }

    FILE *file = fopen(argv[1], "r");
    if (file == NULL) {
        perror("Помилка відкриття файлу");
        return 1;
    }

    char line[256];
    while (fgets(line, sizeof(line), file) != NULL) {
        if (strstr(line, argv[2]) != NULL) {
            printf("%s", line);
        }
    }

    fclose(file);
    return 0;
}
