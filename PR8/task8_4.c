#include <stdio.h>
#include <unistd.h>

int main() {
    int pid = fork();
    if (pid < 0) {
        perror("Помилка fork");
        return 1;
    }
    printf("%d\n", pid);
    return 0;
}
