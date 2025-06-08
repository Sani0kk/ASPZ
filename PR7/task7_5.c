#include <stdio.h>
#include <dirent.h>
#include <string.h>

void list_files(const char *path) {
    DIR *dir = opendir(path);
    if (dir == NULL) {
        perror("Помилка відкриття каталогу");
        return;
    }

    struct dirent *entry;
    while ((entry = readdir(dir)) != NULL) {
        if (entry->d_name[0] == '.') continue;
        char full_path[512];
        snprintf(full_path, sizeof(full_path), "%s/%s", path, entry->d_name);
        printf("%s\n", full_path);
        if (entry->d_type == DT_DIR) {
            list_files(full_path);
        }
    }

    closedir(dir);
}

int main() {
    list_files(".");
    return 0;
}
