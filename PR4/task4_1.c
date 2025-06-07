#include <stdio.h>
  #include <stdlib.h>
  #include <stdint.h>

  int main() {
      size_t max_size = SIZE_MAX;
      printf("Максимальне значення size_t: %zu байтів\n", max_size);
      void *ptr = malloc(max_size);
      if (ptr == NULL) {
          printf("malloc(%zu) повернув NULL (пам’ять не виділена)\n", max_size);
      } else {
          printf("Пам’ять успішно виділена: %p\n", ptr);
          free(ptr);
      }
      return 0;
  }
