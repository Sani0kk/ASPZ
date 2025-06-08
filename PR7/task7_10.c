#include <stdio.h>
  #include <stdlib.h>
  #include <time.h>

  int main(int argc, char *argv[]) {
      srand(time(NULL)); // Встановлюємо унікальне початкове значення
      if (argc != 2) {
          printf("Використання: %s n\n", argv[0]);
          return 1;
      }
      double n = atof(argv[1]);
      for (int i = 0; i < 5; i++) {
          double r1 = (double)rand() / RAND_MAX; // 0.0 до 1.0
          double r2 = r1 * n; // 0.0 до n
          printf("0.0-1.0: %.2f, 0.0-%.2f: %.2f\n", r1, n, r2);
      }
      return 0;
  }
