#include <stdio.h>
#include <stdlib.h>

int global_var = 42; // у data segment
static int static_var = 99; // також у data segment
const char* const_str = "Hello"; // string literal у text/rodata
char bss_var[10000]; // у BSS

void show_addresses() {
    int stack_var = 1;
    char large_stack1[10000];
    char large_stack2[10000];
    char large_stack3[10000];

    printf("Stack top is near        : %p\n", &stack_var);
    printf("Heap (malloc) address    : %p\n", malloc(1));
    printf("Global variable address  : %p\n", &global_var);
    printf("Static variable address  : %p\n", &static_var);
    printf("String literal address   : %p\n", const_str);
    printf("BSS segment address      : %p\n", bss_var);
}

int main() {
    show_addresses();
    return 0;
}