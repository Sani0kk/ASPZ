#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main() {
    size_t megabytes = 0;
    while (1) {
        void *ptr = malloc(1024 * 1024); 
        if (!ptr) {
            printf("Memory allocation failed at ~%zu MB\n", megabytes);
            break;
        }
        megabytes++;
        printf("Allocated %zu MB\n", megabytes);
        usleep(10000); 
    }
    return 0;
}
