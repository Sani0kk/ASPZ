#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/stat.h>
int main() {
    const char *file = "testnodata.txt";
    int fd = open(file, O_CREAT | O_WRONLY, 0000);
    write(fd, "data", 4);
    close(fd);
    chmod(file, 0000);
    printf("Права зняті. Спроба читання...\n");
    int fd2 = open(file, O_RDONLY);
    if (fd2 == -1) perror("open");
    else close(fd2);
    return 0;
}
