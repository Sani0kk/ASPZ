#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <sys/stat.h>
#include <string.h>

int main() {
    DIR *dir = opendir(".");
    struct dirent *entry;

    while ((entry = readdir(dir)) != NULL) {
        if (strstr(entry->d_name, ".out") || strcmp(entry->d_name, "a.out") == 0) {
            printf("Allow read permission for others to %s? (y/n): ", entry->d_name);
            char c = getchar();
            while (getchar() != '\n');
            if (c == 'y' || c == 'Y') {
                chmod(entry->d_name, S_IRUSR | S_IRGRP | S_IROTH | S_IWUSR | S_IXUSR);
            }
        }
    }
    closedir(dir);
    return 0;
}
