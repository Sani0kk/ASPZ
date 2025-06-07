#include <stdio.h>
#include <stdlib.h>
#include <sys/resource.h>

void set_stack_limit(size_t size) {
    struct rlimit rl;
    rl.rlim_cur = size;
    rl.rlim_max = size;
    setrlimit(RLIMIT_STACK, &rl);
}

void recurse(int depth) {
    char arr[1024];
    printf("Depth: %d, addr: %p\n", depth, &arr);
    recurse(depth + 1);
}

int main() {
    set_stack_limit(16 * 1024); 
    recurse(1);
    return 0;
}
