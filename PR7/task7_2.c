#include <stdio.h>
#include <dirent.h>
#include <sys/stat.h>
#include <pwd.h>
#include <grp.h>
#include <time.h>

int main() {
    DIR *dir = opendir(".");
    if (dir == NULL) {
        perror("Помилка відкриття каталогу");
        return 1;
    }

    struct dirent *entry;
    struct stat fileStat;
    while ((entry = readdir(dir)) != NULL) {
        if (stat(entry->d_name, &fileStat) == -1) continue;
        struct passwd *pw = getpwuid(fileStat.st_uid);
        struct group *gr = getgrgid(fileStat.st_gid);
        char time_buf[20];
        strftime(time_buf, sizeof(time_buf), "%b %d %H:%M", localtime(&fileStat.st_mtime));
        printf("%c%c%c%c%c%c%c%c%c%c %s %s %5lld %s %s\n",
               (S_ISDIR(fileStat.st_mode)) ? 'd' : '-',
               (fileStat.st_mode & S_IRUSR) ? 'r' : '-',
               (fileStat.st_mode & S_IWUSR) ? 'w' : '-',
               (fileStat.st_mode & S_IXUSR) ? 'x' : '-',
               (fileStat.st_mode & S_IRGRP) ? 'r' : '-',
               (fileStat.st_mode & S_IWGRP) ? 'w' : '-',
               (fileStat.st_mode & S_IXGRP) ? 'x' : '-',
               (fileStat.st_mode & S_IROTH) ? 'r' : '-',
               (fileStat.st_mode & S_IWOTH) ? 'w' : '-',
               (fileStat.st_mode & S_IXOTH) ? 'x' : '-',
               pw->pw_name, gr->gr_name, (long long)fileStat.st_size, time_buf, entry->d_name);
    }

    closedir(dir);
    return 0;
}
