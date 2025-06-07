#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <sys/resource.h>

void set_cpu_limit(int seconds) {
    struct rlimit rl;
    rl.rlim_cur = seconds;
    rl.rlim_max = seconds;
    setrlimit(RLIMIT_CPU, &rl);
}

void generate_lottery() {
    int nums[49] = {0}, i = 0;
    while (i < 7) {
        int n = rand() % 49 + 1;
        int duplicate = 0;
        for (int j = 0; j < i; j++) if (nums[j] == n) duplicate = 1;
        if (!duplicate) nums[i++] = n;
    }
    printf("7 з 49: ");
    for (i = 0; i < 7; i++) printf("%d ", nums[i]);
    printf("\n");
}

int main() {
    srand(time(NULL));
    set_cpu_limit(1); 
    generate_lottery();
    return 0;
}

