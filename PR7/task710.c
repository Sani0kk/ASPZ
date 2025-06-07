#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main(int argc, char *argv[]) {
    srand(time(NULL));

    float n = 1.0;
    if (argc == 2) n = atof(argv[1]);

    for (int i = 0; i < 10; i++) {
        float r = ((float) rand() / RAND_MAX) * n;
        printf("%.4f\n", r);
    }

    return 0;
}
