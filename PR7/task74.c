#include <stdio.h>

int main(int argc, char *argv[]) {
    if (argc < 2) {
        printf("Usage: %s <file1> [file2...]\n", argv[0]);
        return 1;
    }

    char line[1024];
    for (int i = 1; i < argc; ++i) {
        FILE *fp = fopen(argv[i], "r");
        if (!fp) {
            perror(argv[i]);
            continue;
        }

        int count = 0;
        while (fgets(line, sizeof(line), fp)) {
            printf("%s", line);
            if (++count % 20 == 0) {
                printf("---Press Enter---");
                getchar();
            }
        }
        fclose(fp);
    }
    return 0;
}
