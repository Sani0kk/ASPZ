#include <stdio.h>
#include <stdlib.h>
#include <sys/resource.h>

int main(int argc, char *argv[]) {
    if (argc != 3) {
        printf("Program need two arguments\n");
        return 1;
    }
    FILE *src = fopen(argv[1], "r");
    if (src == NULL) {
        printf("Cannot open file %s for reading\n", argv[1]);
        return 1;
    }
    FILE *dest = fopen(argv[2], "w");
    if (dest == NULL) {
        printf("Cannot open file %s for writing\n", argv[2]);
        fclose(src);
        return 1;
    }
    struct rlimit rl;
    getrlimit(RLIMIT_FSIZE, &rl);
    rl.rlim_cur = 1024; 
    setrlimit(RLIMIT_FSIZE, &rl);
    char buffer[1024];
    size_t bytes;
    while ((bytes = fread(buffer, 1, sizeof(buffer), src)) > 0) {
        if (fwrite(buffer, 1, bytes, dest) != bytes) {
            printf("Перевищено ліміт розміру файлу\n");
            break;
        }
    }
    fclose(src);
    fclose(dest);
    return 0;
}
