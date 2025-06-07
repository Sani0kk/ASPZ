#include <stdio.h>

  int main() {
      int value = 42;  
      int *ptr = (int *)value; 
      printf("Значення: %d\n", *ptr); 
      return 0;
  }
