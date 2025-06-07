#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <errno.h>

int main() {
    int pipefd[2];
    char buffer[1024 * 100];
    memset(buffer, 'A', sizeof(buffer));

    pipe(pipefd);
    fcntl(pipefd[1], F_SETFL, O_NONBLOCK); 

    ssize_t count = write(pipefd[1], buffer, sizeof(buffer));
    if (count < sizeof(buffer)) {
        printf("write() записав лише %ld байт із %ld\n", count, sizeof(buffer));
        perror("write");
    } else {
        printf("Усе записано!\n");
    }

    return 0;
}
