# Практична робота №12-13: Обробка SIGBUS

## Мета роботи
Дізнатися, як обробляти помилки доступу до пам’яті через SIGBUS.

## Завдання 12-13.1: Обробник SIGBUS для `mmap` і фізичної пам’яті

### Опис
Створюємо обробник, який розрізняє помилки від `mmap` і фізичної пам’яті.

### Код
```c
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>
#include <sys/mman.h>
#include <fcntl.h>

void sigbus_handler(int sig, siginfo_t *info, void *context) {
    if (info->si_code == BUS_ADRERR) {
        printf("Помилка SIGBUS: Невірна адреса (фізична пам’ять), адреса: %p\n", info->si_addr);
    } else if (info->si_code == BUS_OBJERR) {
        printf("Помилка SIGBUS: Помилка об’єкта (mmap), адреса: %p\n", info->si_addr);
    } else {
        printf("Невідома помилка SIGBUS, адреса: %p\n", info->si_addr);
    }
    exit(1);
}

int main() {
    struct sigaction sa;
    sa.sa_sigaction = sigbus_handler;
    sa.sa_flags = SA_SIGINFO;
    sigemptyset(&sa.sa_mask);
    if (sigaction(SIGBUS, &sa, NULL) == -1) {
        perror("Помилка встановлення обробника");
        return 1;
    }

    int fd = open("test.txt", O_RDWR | O_CREAT | O_TRUNC, 0644);
    if (fd == -1) {
        perror("Помилка відкриття файлу");
        return 1;
    }
    write(fd, "123", 3);
    void *addr = mmap(NULL, 4096, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);
    if (addr == MAP_FAILED) {
        perror("Помилка mmap");
        close(fd);
        return 1;
    }
    printf("Відображено: %p\n", addr);
    char *p = (char *)addr;
    p[0] = 'A';
    printf("Записано: %c\n", p[0]);
    p += 4096;
    *p = 'B';
    close(fd);
    return 0;
}
```
**Пояснення**: Програма ловить помилки, коли пам’ять не працює правильно, і показує, чи проблема в файлі, чи в пам’яті.

### Компіляція
```sh
gcc -Wall -o task12_1 task12_1.c
```

### Виконання
```sh
./task12_1
```

### Скріншот
![Скріншот завдання 12-13.1](task12_1_screenshot.png)

## Висновок
Дізналися, як обробляти SIGBUS і розрізняти його причини.
