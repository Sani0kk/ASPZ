#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>

int main() {
    int fd = open("sample.txt", O_RDWR);
    if (fd < 0) {
        perror("open");
        return 1;
    }

    off_t pos = lseek(fd, 0, SEEK_CUR); 

    pwrite(fd, "Z", 1, 0);

    lseek(fd, pos, SEEK_SET); 

    close(fd);
    return 0;
}
