# Практична робота №12: Обробка SIGBUS

## Мета роботи
Дізнатися, як обробляти сигнали SIGBUS при роботі з відображенням пам’яті через `mmap`.

## Завдання 12.1: Обробник SIGBUS для `mmap`

### Опис
Ця програма демонструє обробку сигналу SIGBUS, який виникає при спробі доступу до некоректно відображеної пам’яті. Використовується `mmap` для відображення файлу, а обробник розрізняє причини SIGBUS (наприклад, `BUS_ADRERR` або `BUS_OBJERR`).

### Код
```c
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <sys/mman.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>

void sigbus_handler(int sig, siginfo_t *info, void *context) {
    printf("SIGBUS caught!\n");
    if (info->si_code == BUS_ADRERR) {
        printf("BUS_ADRERR: invalid address alignment.\n");
    } else if (info->si_code == BUS_OBJERR) {
        printf("BUS_OBJERR: hardware error accessing object (file I/O).\n");
    } else {
        printf("Other SIGBUS cause: si_code = %d\n", info->si_code);
    }
    exit(EXIT_FAILURE);
}

int main() {
    const char *filename = "test_file.txt";
    int fd = open(filename, O_RDWR | O_CREAT, 0666);
    if (fd < 0) {
        perror("open");
        return 1;
    }

    const char *content = "Test content\n";
    if (write(fd, content, strlen(content)) < 0) {
        perror("write");
        return 1;
    }

    // Викликає SIGBUS при доступі
    ftruncate(fd, 0);

    struct sigaction sa;
    sa.sa_sigaction = sigbus_handler;
    sigemptyset(&sa.sa_mask);
    sa.sa_flags = SA_SIGINFO;

    if (sigaction(SIGBUS, &sa, NULL) == -1) {
        perror("sigaction");
        return 1;
    }

    char *map = mmap(NULL, 4096, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);
    if (map == MAP_FAILED) {
        perror("mmap");
        return 1;
    }

    printf("Trying to write to mapped memory...\n");
    map[0] = 'X';

    munmap(map, 4096);
    close(fd);
    return 0;
}
```
**Пояснення**: Програма створює файл, записує в нього дані, відображає його в пам’ять через `mmap`, а потім викликає SIGBUS через `ftruncate`, який обнуляє розмір файлу, після чого доступ до `map[0]` має викликати помилку.

### Скріншот
![image](https://github.com/user-attachments/assets/cd0b3801-e5ec-44c1-bcc6-7e9e141982ea)

## Висновок
Дізналися, як обробляти SIGBUS при роботі з відображенням пам’яті та як відрізняти причини помилок.
