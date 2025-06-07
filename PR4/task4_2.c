#include <stdio.h>
  #include <stdlib.h>

  int main() {
      int xa = -2, xb = 3;
      int num = xa * xb; 
      printf("num = %d\n", num);
      void *ptr = malloc(num);
      if (ptr == NULL) {
          printf("malloc(%d) повернув NULL\n", num);
      } else {
          printf("Пам’ять виділена: %p\n", ptr);
          free(ptr);
      }
      return 0;
  }
