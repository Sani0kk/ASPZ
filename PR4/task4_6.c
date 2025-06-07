#include <stdio.h>
  #include <stdlib.h>

  int main() {
      void *ptr1 = realloc(NULL, 100); 
      void *ptr2 = realloc(ptr1, 0);  
      if (ptr1 == NULL) {
          printf("ptr1 NULL після realloc(NULL, 100)\n");
      } else {
          printf("ptr1: %p\n", ptr1);
          free(ptr1);
      }
      if (ptr2 == NULL) {
          printf("ptr2 NULL після realloc(..., 0)\n");
      } else {
          printf("ptr2: %p\n", ptr2);
      }
      return 0;
  }
