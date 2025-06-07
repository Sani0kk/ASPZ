#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>

int main() {
    pid_t pid1, pid2;

    printf("Start: PID = %d\n", getpid());

    pid1 = fork(); 

    if (pid1 == 0) {
        printf("After 1st fork (child): PID = %d, PPID = %d\n", getpid(), getppid());
    } else {
        printf("After 1st fork (parent): PID = %d, Child PID = %d\n", getpid(), pid1);
    }

    pid2 = fork();

    if (pid2 == 0) {
        printf("After 2nd fork (child): PID = %d, PPID = %d\n", getpid(), getppid());
    } else {
        printf("After 2nd fork (parent): PID = %d, Child PID = %d\n", getpid(), pid2);
    }

    return 0;
}
