#include <stdio.h>
#include <stdlib.h>

int main() {
    FILE *fp;
    char buffer[1024];

    fp = popen("rwho | more", "r");
    if (fp == NULL) {
        perror("popen");
        return 1;
    }

    while (fgets(buffer, sizeof(buffer), fp)) {
        fputs(buffer, stdout);
    }

    pclose(fp);
    return 0;
}
