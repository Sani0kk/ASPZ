#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <signal.h>
#include <unistd.h>
#include <sys/resource.h>
#include <errno.h>

#define FILE_NAME "dice_rolls.txt"
#define MAX_ROLLS 1000000

void set_file_size_limit(rlim_t limit_bytes) {
    struct rlimit rl;
    rl.rlim_cur = limit_bytes;
    rl.rlim_max = limit_bytes;
    if (setrlimit(RLIMIT_FSIZE, &rl) != 0) {
        perror("Failed to set file size limit");
        exit(EXIT_FAILURE);
    }
}

int main() {
    srand(time(NULL));
    set_file_size_limit(1024); // 1 KB обмеження на розмір файлу

    FILE *file = fopen(FILE_NAME, "w");
    if (!file) {
        perror("Failed to open file");
        return EXIT_FAILURE;
    }

    for (int i = 0; i < MAX_ROLLS; ++i) {
        int roll = rand() % 6 + 1;
        if (fprintf(file, "Roll %d: %d\n", i + 1, roll) < 0) {
            if (errno == EFBIG) {
                fprintf(stderr, "File size limit exceeded. Stopping.\n");
                break;
            } else {
                perror("Write error");
                break;
            }
        }
    }

    fclose(file);
    return 0;
}
