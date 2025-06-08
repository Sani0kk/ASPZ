#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>  // Для strerror
#include <errno.h>   // Для errno

int main() {
    const char *file = "no_access.txt";
    int fd = open(file, O_CREAT | O_WRONLY, 0000);
    if (fd < 0) {
        perror("Помилка створення файлу");
        exit(EXIT_FAILURE);
    }
    if (write(fd, "Конфіденційні дані", 18) < 0) {
        perror("Помилка запису");
        close(fd);
        exit(EXIT_FAILURE);
    }
    close(fd);

    fd = open(file, O_RDONLY);
    if (fd < 0) {
        printf("Читання неможливе: %s\n", strerror(errno));
    } else {
        char buf[256];
        ssize_t bytes_read = read(fd, buf, sizeof(buf) - 1); // -1 для нульового терміну
        if (bytes_read < 0) {
            perror("Помилка читання");
        } else {
            buf[bytes_read] = '\0'; // Додаємо нульовий термінатор
            printf("Вміст: %s\n", buf);
        }
        close(fd);
    }

    return 0;
}
