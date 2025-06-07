#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>

int main() {
    const char *filename = "/tmp/testfile.txt";
    int fd = open(filename, O_CREAT | O_WRONLY, 0644);
    write(fd, "Hello from user\n", 17);
    close(fd);

    printf("Файл створено. Запустіть цю програму від імені root для копіювання.\n");

    if (getuid() == 0) {
        system("cp /tmp/testfile.txt /home/korystuvach/testfile_copy.txt");
        system("chown korystuvach:korystuvach /home/korystuvach/testfile_copy.txt");
    }
    return 0;
}
