#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/mman.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <ucontext.h>
#include <errno.h>

void sigbus_handler(int sig, siginfo_t *si, void *context) {
    printf("SIGBUS received!\n");

    void *fault_addr = si->si_addr;
    int code = si->si_code;

    printf("Fault address: %p\n", fault_addr);

    switch (code) {
        case BUS_ADRALN:
            printf("Cause: Invalid address alignment (likely hardware)\n");
            break;
        case BUS_ADRERR:
            printf("Cause: Physical address error (likely invalid memory)\n");
            break;
        case BUS_OBJERR:
            printf("Cause: Object-specific hardware error (e.g., mmap to truncated file)\n");
            break;
        default:
            printf("Cause: Unknown (code %d)\n", code);
    }

    _exit(1); 
}

int main() {
    struct sigaction sa;
    sa.sa_flags = SA_SIGINFO;
    sa.sa_sigaction = sigbus_handler;
    sigemptyset(&sa.sa_mask);
    sigaction(SIGBUS, &sa, NULL);

    const char *filename = "testfile.txt";
    int fd = open(filename, O_RDWR | O_CREAT, 0600);
    write(fd, "12345", 5); 
    size_t size = getpagesize();
    char *map = mmap(NULL, size, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);
    close(fd);

    printf("File mapped. Now truncating it.\n");
    truncate(filename, 2);

    printf("Reading beyond truncated size (this should trigger SIGBUS)...\n");
    char c = map[4]; 
    printf("Read char: %c\n", c);

    munmap(map, size);
    return 0;
}
