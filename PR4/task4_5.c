#include <stdio.h>
  #include <stdlib.h>
  #include <sys/resource.h>

  int main() {
      struct rlimit rl;
      getrlimit(RLIMIT_AS, &rl);
      rl.rlim_cur = 1024 * 1024;
      setrlimit(RLIMIT_AS, &rl);
      void *ptr = malloc(512 * 1024);
      if (ptr == NULL) {
          printf("Помилка початкового malloc\n");
          return 1;
      }
      void *new_ptr = realloc(ptr, 2 * 1024 * 1024); 
      if (new_ptr == NULL) {
          printf("realloc не зміг виділити 2 МБ, ptr збережено: %p\n", ptr);
      } else {
          printf("realloc успішно: %p\n", new_ptr);
          ptr = new_ptr;
      }
      free(ptr);
      return 0;
  }
