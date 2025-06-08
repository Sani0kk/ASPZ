#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
    const char *dirs[] = {"/home/san", "/usr/bin", "/etc", NULL};
    for (int i = 0; dirs[i] != NULL; i++) {
        char cmd[128];
        snprintf(cmd, sizeof(cmd), "ls -l %s", dirs[i]);
        FILE *ls_pipe = popen(cmd, "r");
        if (ls_pipe == NULL) {
            perror("Помилка виконання ls");
            continue;
        }
        printf("Права для %s:\n", dirs[i]);
        char buf[256];
        while (fgets(buf, sizeof(buf), ls_pipe) != NULL) {
            printf("%s", buf);
        }
        pclose(ls_pipe);

        FILE *cat_pipe = popen("cat", "w");
        if (cat_pipe != NULL) {
            fprintf(cat_pipe, "Спроба читання %s\n", dirs[i]);
            pclose(cat_pipe);
        }
    }
    return 0;
}
