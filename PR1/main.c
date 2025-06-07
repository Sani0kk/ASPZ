#include <stdio.h>
#include "input.h"
#include "output.h"
#include "process1.h"
#include "process.h"

int main() {
    int value = get_input();
    int processed1 = process1(value);
    int processed2 = process(value);
    print_output(processed1, processed2);
    return 0;
}
