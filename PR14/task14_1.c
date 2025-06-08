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

    sa.sa_handler = handler;
    sigemptyset(&sa.sa_mask);
    sa.sa_flags = SA_RESTART; 

    if (sigaction(SIGALRM, &sa, NULL) == -1) {
        perror("sigaction");
        exit(EXIT_FAILURE);
    }

    timer.it_value.tv_sec = 0;
    timer.it_value.tv_usec = 100000;  // 100 мс
    timer.it_interval.tv_sec = 0;
    timer.it_interval.tv_usec = 100000;

    if (setitimer(ITIMER_REAL, &timer, NULL) == -1) {
        perror("setitimer");
        exit(EXIT_FAILURE);
    }

    while (1) {
        usleep(1000); 
    }

    return 0;
}
