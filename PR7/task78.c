#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <string.h>
#include <unistd.h>

int main() {
    DIR *dir = opendir(".");
    struct dirent *entry;

    while ((entry = readdir(dir)) != NULL) {
        if (entry->d_type == DT_REG) {
            printf("Delete file %s? (y/n): ", entry->d_name);
            char c = getchar();
            while (getchar() != '\n');
            if (c == 'y' || c == 'Y') {
                remove(entry->d_name);
            }
        }
    }
    closedir(dir);
    return 0;
}
