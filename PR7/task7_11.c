#include <stdio.h>
  #include <dirent.h>
  #include <sys/stat.h>
  #include <time.h>

  int main() {
      DIR *dir = opendir(".");
      if (dir == NULL) {
          printf("Не можу відкрити теку\n");
          return 1;
      }
      time_t now = time(NULL);
      time_t weekAgo = now - 7 * 24 * 3600;
      struct dirent *entry;
      while ((entry = readdir(dir)) != NULL) {
          if (entry->d_name[0] == '.') continue;
          struct stat fileStat;
          if (stat(entry->d_name, &fileStat) == -1) continue;
          if (fileStat.st_mtime > weekAgo) {
              printf("%s (змінено: %s)", entry->d_name, ctime(&fileStat.st_mtime));
          }
      }
      closedir(dir);
      return 0;
  }
