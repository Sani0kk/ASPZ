#include <stdio.h>
  #include <stdlib.h>
  #include <pthread.h>

  void *thread_func(void *arg) {
      void *ptr = malloc(100);
      if (ptr == NULL) {
          printf("Потік: Помилка malloc\n");
      } else {
          printf("Потік %ld: Пам’ять виділено: %p\n", (long)arg, ptr);
      }
      sleep(1);
      free(ptr);
      return NULL;
  }

  int main() {
      pthread_t threads[5];
      for (long i = 0; i < 5; i++) {
          pthread_create(&threads[i], NULL, thread_func, (void *)i);
      }
      for (int i = 0; i < 5; i++) {
          pthread_join(threads[i], NULL);
      }
      return 0;
  }
