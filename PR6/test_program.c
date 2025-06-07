#include <stdlib.h>
  #include <stdio.h>

  int main() {
      int *ptr = malloc(10 * sizeof(int));
      if (ptr == NULL) {
          printf("Помилка виділення\n");
          return 1;
      }
      printf("Пам’ять виділено: %p\n", (void *)ptr);
      return 0;
  }
