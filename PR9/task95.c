#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>
int main() {
    int fd = open("tempfile.txt", O_CREAT | O_RDWR, 0600);
    if (fd == -1) return 1;
    write(fd, "some text", 9);
    close(fd);
    printf("Файл створено. Запустіть: sudo chown root tempfile.txt && sudo chmod 400 tempfile.txt\n");
    return 0;
}
