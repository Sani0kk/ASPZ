#include <stdio.h>
  #include <dirent.h>
  #include <sys/stat.h>
  #include <string.h>

  int main() {
      DIR *dir = opendir(".");
      if (dir == NULL) {
          printf("Не можу відкрити теку\n");
          return 1;
      }
      struct dirent *entry;
      while ((entry = readdir(dir)) != NULL) {
          if (entry->d_name[0] == '.') continue;
          char *ext = strrchr(entry->d_name, '.');
          if (ext && strcmp(ext, ".c") == 0) {
              printf("Файл: %s\n", entry->d_name);
              printf("Дати дозвіл на читання іншим? (y/n): ");
              char choice;
              scanf(" %c", &choice);
              if (choice == 'y' || choice == 'Y') {
                  chmod(entry->d_name, S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
                  printf("Дозвіл надано\n");
              }
          }
      }
      closedir(dir);
      return 0;
  }
