#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>

int main() {
    const char *file = "no_access.txt";
    int fd = open(file, O_CREAT | O_WRONLY, 0000);
    if (fd < 0) {
        perror("Помилка створення файлу");
        exit(EXIT_FAILURE);
    }
    write(fd, "Конфіденційні дані", 18);
    close(fd);

    fd = open(file, O_RDONLY);
    if (fd < 0) {
        printf("Читання неможливе: %s\n", strerror(errno));
    } else {
        char buf[256];
        read(fd, buf, sizeof(buf));
        printf("Вміст: %s\n", buf);
        close(fd);
    }

    return 0;
}
