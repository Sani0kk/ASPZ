#include <stdio.h>
  #include <dirent.h>
  #include <string.h>

  int main() {
      DIR *dir = opendir(".");
      if (dir == NULL) {
          printf("Не можу відкрити теку\n");
          return 1;
      }
      struct dirent *entry;
      char dirs[100][256];
      int dirCount = 0;
      while ((entry = readdir(dir)) != NULL) {
          if (entry->d_type == DT_DIR && entry->d_name[0] != '.') {
              strcpy(dirs[dirCount++], entry->d_name);
          }
      }
      closedir(dir);
      for (int i = 0; i < dirCount - 1; i++) {
          for (int j = i + 1; j < dirCount; j++) {
              if (strcmp(dirs[i], dirs[j]) > 0) {
                  char temp[256];
                  strcpy(temp, dirs[i]);
                  strcpy(dirs[i], dirs[j]);
                  strcpy(dirs[j], temp);
              }
          }
      }
      for (int i = 0; i < dirCount; i++) {
          printf("%s\n", dirs[i]);
      }
      return 0;
  }
