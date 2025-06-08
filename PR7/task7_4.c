#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
    if (argc < 2) {
        printf("Використання: %s файл1 [файл2 ...]\n", argv[0]);
        return 1;
    }

    for (int i = 1; i < argc; i++) {
        FILE *file = fopen(argv[i], "r");
        if (file == NULL) {
            printf("Не можу відкрити %s\n", argv[i]);
            continue;
        }

        char line[256];
        int count = 0;
        while (fgets(line, sizeof(line), file) != NULL) {
            printf("%s", line);
            count++;
            if (count % 20 == 0) {
                printf("Натисніть Enter для продовження...");
                getchar();
            }
        }

        fclose(file);
    }

    return 0;
}
