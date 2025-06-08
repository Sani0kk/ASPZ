#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>

int main() {
    int fd = open("test.txt", O_RDWR | O_CREAT | O_TRUNC, 0644);
    if (fd < 0) {
        perror("Помилка відкриття файлу");
        exit(EXIT_FAILURE);
    }

    write(fd, "123456789", 9);
    off_t pos = lseek(fd, 0, SEEK_CUR);
    pwrite(fd, "XXX", 3, 0); // Змінюємо перші 3 байти
    printf("Позиція: %jd, вміст змінено на місці\n", (intmax_t)pos);

    close(fd);
    return 0;
}
