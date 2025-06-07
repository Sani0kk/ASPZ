#include <stdio.h>
  #include <stdlib.h>

  int main() {
      void *ptr = NULL;
      int i = 0;
      while (i < 3) {
          if (!ptr) {
              ptr = malloc(100);
              if (ptr == NULL) {
                  printf("Помилка виділення пам’яті\n");
                  return 1;
              }
          }
          printf("Використання ptr: %p\n", ptr);
          free(ptr); 
          i++;
      }
      return 0;
  }
