#include <stdio.h>
#include <dirent.h>
#include <string.h>
#include <stdlib.h>

int compare(const void *a, const void *b) {
    return strcmp(*(const char **)a, *(const char **)b);
}

int main() {
    DIR *dir = opendir(".");
    if (dir == NULL) {
        perror("Помилка відкриття каталогу");
        return 1;
    }

    struct dirent *entry;
    char *dirs[100];
    int dir_count = 0;
    while ((entry = readdir(dir)) != NULL) {
        if (entry->d_type == DT_DIR && entry->d_name[0] != '.') {
            dirs[dir_count++] = strdup(entry->d_name);
        }
    }
    closedir(dir);

    qsort(dirs, dir_count, sizeof(char *), compare);
    for (int i = 0; i < dir_count; i++) {
        printf("%s\n", dirs[i]);
        free(dirs[i]);
    }

    return 0;
}
