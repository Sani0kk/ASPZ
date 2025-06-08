#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main(int argc, char *argv[]) {
    if (argc != 2) {
        printf("Використання: %s n\n", argv[0]);
        return 1;
    }

    double n = atof(argv[1]);
    srand(time(NULL));

    for (int i = 0; i < 5; i++) {
        double r1 = (double)rand() / RAND_MAX;
        double r2 = r1 * n;
        printf("0.0-1.0: %.2f, 0.0-%.2f: %.2f\n", r1, n, r2);
    }

    return 0;
}
