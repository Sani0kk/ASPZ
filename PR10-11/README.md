# Практична робота №10: Робота з `fork()`

## Мета роботи
Дізнатися, як створюються процеси за допомогою `fork()`.

## Завдання 10.1: Два `fork()` поспіль

### Опис
Створюємо два дочірні процеси і показуємо їхні PID.

### Код
```c
#include <stdio.h>
#include <unistd.h>

int main() {
    pid_t pid1 = fork();
    if (pid1 == 0) {
        printf("Процес 1 (дочірній від 1-го): PID = %d, PPID = %d\n", getpid(), getppid());
    } else if (pid1 > 0) {
        pid_t pid2 = fork();
        if (pid2 == 0) {
            printf("Процес 2 (дочірній від 2-го): PID = %d, PPID = %d\n", getpid(), getppid());
        } else if (pid2 > 0) {
            printf("Процес 0 (батьківський): PID = %d, PPID = %d\n", getpid(), getppid());
        }
    }
    return 0;
}
```
**Пояснення**: Програма ділить процес на три, показуючи, хто звідки прийшов.

### Скріншот
![image](https://github.com/user-attachments/assets/f99aadb2-fe45-4d0d-9ec1-2eba95578a3d)

## Висновок
Побачили, що два `fork()` створюють 4 процеси, і кожен має свій унікальний PID.
