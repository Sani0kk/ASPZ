#include <stdio.h>
#include <sys/resource.h>

void recursive(int depth) {
    int x[1000];
    if (depth > 0) recursive(depth - 1);
}

int main() {
    struct rlimit rl;
    getrlimit(RLIMIT_STACK, &rl);
    rl.rlim_cur = 8192;
    setrlimit(RLIMIT_STACK, &rl);
    recursive(1000);
    printf("Стек не переповнився\n");
    return 0;
}
