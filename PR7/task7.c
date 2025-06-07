#include <stdio.h>
#include <sys/stat.h>
#include <time.h>
#include <dirent.h>

int main() {
    DIR *dir = opendir(".");
    struct dirent *entry;
    time_t now = time(NULL);

    while ((entry = readdir(dir)) != NULL) {
        struct stat st;
        if (stat(entry->d_name, &st) == 0 && S_ISREG(st.st_mode)) {
            double days = difftime(now, st.st_mtime) / (60 * 60 * 24);
            if (days <= 7.0) {
                printf("%s - modified %.2f days ago\n", entry->d_name, days);
            }
        }
    }
    closedir(dir);
    return 0;
}
