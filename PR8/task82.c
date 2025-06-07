#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>

int main() {
    int fd = open("example.bin", O_RDONLY);
    if (fd < 0) {
        perror("open");
        return 1;
    }

    unsigned char buffer[4];
    lseek(fd, 3, SEEK_SET);
    read(fd, buffer, 4);

    printf("Прочитані байти:\n");
    for (int i = 0; i < 4; i++) {
        printf("%u ", buffer[i]);
    }
    printf("\n");

    close(fd);
    return 0;
}
