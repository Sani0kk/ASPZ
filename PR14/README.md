# Практична робота №14: Робота з таймером

## Мета роботи
Дізнатися, як використовувати таймери для періодичного оновлення лічильника та його вимкнення через заданий час.

## Завдання 14.1: Оновлення лічильника та вимкнення таймера

### Опис
Ця програма налаштовує таймер, який кожні 100 мс збільшує лічильник і виводить його значення. Після досягнення значення 50 (приблизно 5 секунд), таймер вимикається, і програма завершує роботу. Використовується активне очікування з `usleep` замість `pause()`.

### Код
```c
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <sys/time.h>

volatile sig_atomic_t counter = 0;

void handler(int sig) {
    counter++;
    printf("Лічильник: %d\n", counter);
    fflush(stdout);

    if (counter >= 50) {
        printf("Таймер вимкнено після 5 секунд.\n");
        fflush(stdout);
        exit(0);
    }
}

int main() {
    struct sigaction sa;
    struct itimerval timer;

    // Налаштування обробника сигналу
    sa.sa_handler = handler;
    sigemptyset(&sa.sa_mask);
    sa.sa_flags = SA_RESTART; // щоб сигнал не переривав системні виклики

    if (sigaction(SIGALRM, &sa, NULL) == -1) {
        perror("sigaction");
        exit(EXIT_FAILURE);
    }

    // Налаштування таймера: 100 мс перше спрацювання та кожні 100 мс після
    timer.it_value.tv_sec = 0;
    timer.it_value.tv_usec = 100000;  // 100 мс
    timer.it_interval.tv_sec = 0;
    timer.it_interval.tv_usec = 100000;

    if (setitimer(ITIMER_REAL, &timer, NULL) == -1) {
        perror("setitimer");
        exit(EXIT_FAILURE);
    }

    // Цикл очікування сигналів — не pause(), а просто активне очікування
    while (1) {
        // без pause(); вивід викликається обробником
        usleep(1000);  // трохи розвантажує CPU
    }

    return 0;
}
```
**Пояснення**: Програма налаштовує сигнал SIGALRM через `setitimer` для періодичного виклику `handler` кожні 100 мс. Обробник збільшує лічильник і виводить його значення, а після 50 ітерацій (близько 5 секунд) завершує програму. Активне очікування з `usleep` замінює `pause()` для уникнення переривання.

### Скріншот
![image](https://github.com/user-attachments/assets/0ae7fab0-2eeb-4647-a4d5-47fbde710873)
![image](https://github.com/user-attachments/assets/a50bffb6-3a7c-44e1-a8d5-134390d18f2e)

## Висновок
Дізналися, як налаштовувати таймери для періодичного оновлення лічильника та вимикати їх після досягнення заданого значення, використовуючи активне очікування замість `pause()`.
