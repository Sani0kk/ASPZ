#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <string.h>
#include <time.h>

volatile sig_atomic_t counter = 0;

void timer_handler(int signum) {
    counter++;
    printf("Timer tick: %d (%.1f seconds)\n", counter, counter * 0.1);
    if (counter * 100 >= 5000) {
        printf("Stopping timer after 5 seconds.\n");
        exit(0);
    }
}

int main() {
    struct sigaction sa;
    struct itimerval timer;

    memset(&sa, 0, sizeof(sa));
    sa.sa_handler = &timer_handler;
    sigaction(SIGALRM, &sa, NULL);

    timer.it_value.tv_sec = 0;
    timer.it_value.tv_usec = 100000;
    timer.it_interval.tv_sec = 0;
    timer.it_interval.tv_usec = 100000;

    setitimer(ITIMER_REAL, &timer, NULL);

    while (1) {
        pause();
    }

    return 0;
}
