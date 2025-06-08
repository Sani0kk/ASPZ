#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <sys/time.h>
#include <unistd.h>

volatile sig_atomic_t counter = 0;

void timer_handler(int signum) {
    counter++;
    printf("Лічильник: %d\n", counter);

    if (counter >= 50) {
        // Вимикаємо таймер
        struct itimerval stop = {{0, 0}, {0, 0}};
        setitimer(ITIMER_REAL, &stop, NULL);
        printf("Таймер вимкнено після 5 секунд.\n");
        exit(0); // Завершити програму
    }
}

int main() {
    struct sigaction sa;
    struct itimerval timer;

    // Встановлення обробника сигналу SIGALRM
    sa.sa_handler = timer_handler;
    sa.sa_flags = 0;
    sigemptyset(&sa.sa_mask);
    if (sigaction(SIGALRM, &sa, NULL) == -1) {
        perror("sigaction");
        exit(EXIT_FAILURE);
    }

    // Налаштування таймера: 100 мс інтервал
    timer.it_value.tv_sec = 0;
    timer.it_value.tv_usec = 100000;
    timer.it_interval.tv_sec = 0;
    timer.it_interval.tv_usec = 100000;

    if (setitimer(ITIMER_REAL, &timer, NULL) == -1) {
        perror("setitimer");
        exit(EXIT_FAILURE);
    }

    // Цикл очікування сигналів
    while (1) {
        pause(); // Чекає сигналів
    }

    return 0;
}
