#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
    FILE *fp = popen("getent passwd", "r");
    if (!fp) {
        perror("popen");
        return 1;
    }
    char line[512];
    while (fgets(line, sizeof(line), fp)) {
        char *token = strtok(line, ":");
        int field = 0;
        char username[100];
        int uid = -1;
        while (token) {
            field++;
            if (field == 1) strncpy(username, token, sizeof(username));
            if (field == 3) uid = atoi(token);
            token = strtok(NULL, ":");
        }
        if (uid >= 1000 && uid != getuid()) {
            printf("Знайдено користувача: %s (UID=%d)\n", username, uid);
        }
    }
    pclose(fp);
    return 0;
}
