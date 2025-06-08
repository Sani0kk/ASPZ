#include <stdio.h>
#include <dirent.h>
#include <string.h>
#include <sys/stat.h>

int main() {
    DIR *dir = opendir(".");
    if (dir == NULL) {
        perror("Помилка відкриття каталогу");
        return 1;
    }

    struct dirent *entry;
    while ((entry = readdir(dir)) != NULL) {
        if (strstr(entry->d_name, ".c") != NULL) {
            printf("Файл: %s\n", entry->d_name);
            printf("Надати дозвіл на читання іншим? (y/n): ");
            char choice;
            scanf(" %c", &choice);
            if (choice == 'y' || choice == 'Y') {
                struct stat fileStat;
                stat(entry->d_name, &fileStat);
                chmod(entry->d_name, fileStat.st_mode | S_IROTH);
                printf("Дозвіл надано.\n");
            }
        }
    }

    closedir(dir);
    return 0;
}
