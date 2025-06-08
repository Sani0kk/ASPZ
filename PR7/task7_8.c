#include <stdio.h>
#include <dirent.h>
#include <unistd.h>

int main() {
    DIR *dir = opendir(".");
    if (dir == NULL) {
        perror("Помилка відкриття каталогу");
        return 1;
    }

    struct dirent *entry;
    while ((entry = readdir(dir)) != NULL) {
        if (entry->d_name[0] == '.') continue;
        printf("Видалити %s? (y/n): ", entry->d_name);
        char choice;
        scanf(" %c", &choice);
        if (choice == 'y' || choice == 'Y') {
            if (unlink(entry->d_name) == 0) {
                printf("Файл %s видалено.\n", entry->d_name);
            } else {
                printf("Помилка видалення %s\n", entry->d_name);
            }
        }
    }

    closedir(dir);
    return 0;
}
