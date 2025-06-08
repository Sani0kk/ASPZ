#include <stdio.h>

  int main(int argc, char *argv[]) {
      if (argc < 2) {
          printf("Використання: %s файл1 [файл2 ...]\n", argv[0]);
          return 1;
      }
      for (int i = 1; i < argc; i++) {
          FILE *file = fopen(argv[i], "r");
          if (file == NULL) {
              printf("Не можу відкрити %s\n", argv[i]);
              continue;
          }
          char buffer[1024];
          int line = 0;
          while (fgets(buffer, sizeof(buffer), file) != NULL) {
              printf("%s", buffer);
              line++;
              if (line % 20 == 0) {
                  printf("Натисніть Enter для продовження...");
                  getchar();
              }
          }
          fclose(file);
      }
      return 0;
  }
