#include <stdio.h>
  #include <stdlib.h>

  int main() {
      struct sbar {
          int data;
      };
      struct sbar *ptr = calloc(1000, sizeof(struct sbar));
      if (ptr == NULL) {
          printf("Помилка calloc\n");
          return 1;
      }
      struct sbar *newptr = reallocarray(ptr, 500, sizeof(struct sbar));
      if (newptr == NULL) {
          printf("Помилка reallocarray\n");
          free(ptr);
          return 1;
      }
      printf("Успішно перевиділено: %p\n", newptr);
      free(newptr);
      return 0;
  }
