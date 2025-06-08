#include <stdio.h>
#include <dirent.h>
#include <sys/stat.h>
#include <time.h>

int main() {
    DIR *dir = opendir(".");
    if (dir == NULL) {
        perror("Помилка відкриття каталогу");
        return 1;
    }

    time_t now = time(NULL);
    time_t week_ago = now - 7 * 24 * 3600;

    struct dirent *entry;
    while ((entry = readdir(dir)) != NULL) {
        if (entry->d_name[0] == '.') continue;
        struct stat fileStat;
        if (stat(entry->d_name, &fileStat) == -1) continue;
        if (fileStat.st_mtime > week_ago) {
            char time_buf[20];
            strftime(time_buf, sizeof(time_buf), "%Y-%m-%d %H:%M:%S", localtime(&fileStat.st_mtime));
            printf("%s (змінено: %s)\n", entry->d_name, time_buf);
        }
    }

    closedir(dir);
    return 0;
}
