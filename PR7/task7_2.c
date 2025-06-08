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
      struct dirent *entry;
      struct stat fileStat;
      while ((entry = readdir(dir)) != NULL) {
          if (stat(entry->d_name, &fileStat) == -1) continue;
          printf("%s %ld %s %ld %s", (S_ISDIR(fileStat.st_mode)) ? "d" : "-",
                 fileStat.st_nlink, "user", fileStat.st_size,
                 ctime(&fileStat.st_mtime));
          printf("%s\n", entry->d_name);
      }
      closedir(dir);
      return 0;
  }
