#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>

int main() {
    int fd = open("test.txt", O_WRONLY | O_CREAT | O_TRUNC, 0644);
    if (fd < 0) {
        perror("Помилка відкриття файлу");
        exit(EXIT_FAILURE);
    }

    char buffer[10] = "123456789";
    ssize_t count = write(fd, buffer, 10);
    if (count < 0) {
        perror("Помилка запису");
    } else if (count != 10) {
        printf("Записано %zd байтів замість 10\n", count);
    } else {
        printf("Записано всі 10 байтів\n");
    }

    close(fd);
    return 0;
}
