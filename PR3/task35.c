#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>
#include <sys/resource.h>

int main(int argc, char *argv[]) {
    if (argc != 3) {
        printf("Program need two arguments\n");
        return 1;
    }

    FILE *in = fopen(argv[1], "r");
    if (!in) {
        printf("Cannot open file %s for reading\n", argv[1]);
        return 1;
    }

    FILE *out = fopen(argv[2], "w");
    if (!out) {
        printf("Cannot open file %s for writing\n", argv[2]);
        fclose(in);
        return 1;
    }

    char buf[1024];
    size_t n;
    while ((n = fread(buf, 1, sizeof(buf), in)) > 0) {
        if (fwrite(buf, 1, n, out) < n) {
            if (errno == EFBIG)
                printf("File size limit exceeded\n");
            else
                perror("Write error");
            break;
        }
    }

    fclose(in);
    fclose(out);
    return 0;
}
