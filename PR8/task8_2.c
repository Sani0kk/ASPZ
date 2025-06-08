#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>

int main() {
    int fd = open("data.txt", O_WRONLY | O_CREAT | O_TRUNC, 0644);
    if (fd < 0) {
        perror("Помилка відкриття файлу");
        exit(EXIT_FAILURE);
    }
    char data[] = {4, 5, 2, 2, 3, 3, 7, 9, 1, 5};
    write(fd, data, sizeof(data));
    close(fd);

    fd = open("data.txt", O_RDONLY);
    if (fd < 0) {
        perror("Помилка відкриття файлу");
        exit(EXIT_FAILURE);
    }

    lseek(fd, 3, SEEK_SET);
    char buffer[4];
    ssize_t count = read(fd, buffer, 4);
    if (count < 0) {
        perror("Помилка читання");
    } else {
        printf("Буфер: ");
        for (int i = 0; i < count; i++) {
            printf("%d ", buffer[i]);
        }
        printf("\n");
    }

    close(fd);
    return 0;
}
