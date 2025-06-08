#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>

int main() {
    const char *temp_file = "test_temp.txt";
    int fd = open(temp_file, O_CREAT | O_WRONLY, 0644);
    if (fd < 0) {
        perror("Помилка створення файлу");
        exit(EXIT_FAILURE);
    }
    write(fd, "Тест", 4);
    close(fd);

    if (setuid(0) == -1) {
        perror("Помилка переходу до root");
        exit(EXIT_FAILURE);
    }
    if (getuid() != 0) {
        fprintf(stderr, "Немає root-доступу.\n");
        exit(EXIT_FAILURE);
    }

    if (chown(temp_file, getuid(), getgid()) == -1) {
        perror("Помилка chown");
    }
    if (chmod(temp_file, 0600) == -1) {
        perror("Помилка chmod");
    }

    setuid(getuid());
    fd = open(temp_file, O_RDWR);
    if (fd >= 0) {
        printf("Доступ до файлу для читання/запису.\n");
        close(fd);
    } else {
        printf("Немає доступу: %s\n", strerror(errno));
    }

    return 0;
}
