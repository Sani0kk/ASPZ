#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <string.h>
#include <sys/stat.h>
#include <unistd.h>

void list_dir(const char *path) {
    DIR *dir = opendir(path);
    struct dirent *entry;

    if (!dir) return;

    while ((entry = readdir(dir)) != NULL) {
        char fullpath[1024];
        if (strcmp(entry->d_name, ".") == 0 || strcmp(entry->d_name, "..") == 0) continue;
        snprintf(fullpath, sizeof(fullpath), "%s/%s", path, entry->d_name);
        printf("%s\n", fullpath);

        struct stat st;
        if (stat(fullpath, &st) == 0 && S_ISDIR(st.st_mode)) {
            list_dir(fullpath);
        }
    }
    closedir(dir);
}

int main() {
    list_dir(".");
    return 0;
}
