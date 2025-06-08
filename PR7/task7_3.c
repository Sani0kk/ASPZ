#include <stdio.h>
  #include <string.h>

  int main(int argc, char *argv[]) {
      if (argc != 3) {
          printf("Використання: %s файл слово\n", argv[0]);
          return 1;
      }
      FILE *file = fopen(argv[1], "r");
      if (file == NULL) {
          printf("Не можу відкрити файл\n");
          return 1;
      }
      char buffer[1024];
      while (fgets(buffer, sizeof(buffer), file) != NULL) {
          if (strstr(buffer, argv[2]) != NULL) {
              printf("%s", buffer);
          }
      }
      fclose(file);
      return 0;
  }
