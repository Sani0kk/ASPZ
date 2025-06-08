#include <stdio.h>
  #include <dirent.h>

  void listDir(const char *path) {
      DIR *dir = opendir(path);
      if (dir == NULL) return;
      struct dirent *entry;
      while ((entry = readdir(dir)) != NULL) {
          if (entry->d_name[0] == '.') continue;
          printf("%s/%s\n", path, entry->d_name);
          if (entry->d_type == DT_DIR) {
              char newPath[256];
              snprintf(newPath, sizeof(newPath), "%s/%s", path, entry->d_name);
              listDir(newPath);
          }
      }
      closedir(dir);
  }

  int main() {
      listDir(".");
      return 0;
  }
