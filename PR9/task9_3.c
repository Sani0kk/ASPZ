#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>

int main() {
    const char *source = "user_temp.txt";
    const char *dest = "/home/san/copied_temp.txt";

    int fd = open(source, O_CREAT | O_WRONLY, 0644);
    if (fd < 0) {
        perror("Помилка створення файлу");
        exit(EXIT_FAILURE);
    }
    write(fd, "Тестовий вміст", 14);
    close(fd);

    if (setuid(0) == -1) {
        perror("Помилка переходу до root");
        exit(EXIT_FAILURE);
    }
    if (getuid() != 0) {
        fprintf(stderr, "Немає root-доступу.\n");
        exit(EXIT_FAILURE);
    }

    if (link(source, dest) == -1) {
        perror("Помилка копіювання");
        exit(EXIT_FAILURE);
    }
    printf("Файл скопійовано до %s.\n", dest);

    setuid(getuid());
    fd = open(dest, O_WRONLY);
    if (fd < 0) {
        printf("Помилка запису: %s (немає прав).\n", strerror(errno));
    } else {
        write(fd, "Спроба зміни", 12);
        close(fd);
    }

    if (unlink(dest) == -1) {
        printf("Помилка видалення: %s (немає прав).\n", strerror(errno));
    } else {
        printf("Файл видалено.\n");
    }

    return 0;
}
