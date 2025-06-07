#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <sys/stat.h>
#include <string.h>

#define MAX_DIRS 1024

int main() {
    DIR *dir = opendir(".");
    struct dirent *entry;
    char *dirs[MAX_DIRS];
    int count = 0;

    while ((entry = readdir(dir)) != NULL) {
        struct stat st;
        if (stat(entry->d_name, &st) == 0 && S_ISDIR(st.st_mode) &&
            strcmp(entry->d_name, ".") != 0 && strcmp(entry->d_name, "..") != 0) {
            dirs[count++] = strdup(entry->d_name);
        }
    }
    closedir(dir);

    qsort(dirs, count, sizeof(char*), (int(*)(const void*, const void*))strcmp);
    for (int i = 0; i < count; ++i) {
        printf("%s\n", dirs[i]);
        free(dirs[i]);
    }
    return 0;
}
