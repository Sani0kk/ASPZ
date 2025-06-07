#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>

int main() {
    int fd[1000];
    for (int i = 0; i < 1000; i++) {
        fd[i] = open("/dev/null", O_RDONLY);
        if (fd[i] < 0) {
            printf("Помилка при відкритті файлу %d\n", i);
            break;
        }
    }
    for (int i = 0; i < 1000; i++) {
        if (fd[i] >= 0) close(fd[i]);
    }
    return 0;
}
