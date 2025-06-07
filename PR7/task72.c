#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <sys/stat.h>
#include <pwd.h>
#include <grp.h>
#include <time.h>

void print_permissions(mode_t mode) {
    char perms[11] = "----------";
    if (S_ISDIR(mode)) perms[0] = 'd';
    if (S_ISLNK(mode)) perms[0] = 'l';
    if (mode & S_IRUSR) perms[1] = 'r';
    if (mode & S_IWUSR) perms[2] = 'w';
    if (mode & S_IXUSR) perms[3] = 'x';
    if (mode & S_IRGRP) perms[4] = 'r';
    if (mode & S_IWGRP) perms[5] = 'w';
    if (mode & S_IXGRP) perms[6] = 'x';
    if (mode & S_IROTH) perms[7] = 'r';
    if (mode & S_IWOTH) perms[8] = 'w';
    if (mode & S_IXOTH) perms[9] = 'x';
    printf("%s ", perms);
}

int main() {
    DIR *dir = opendir(".");
    struct dirent *entry;
    struct stat st;
    struct passwd *pwd;
    struct group *grp;
    char timebuf[64];

    while ((entry = readdir(dir)) != NULL) {
        stat(entry->d_name, &st);
        print_permissions(st.st_mode);
        printf("%lu ", st.st_nlink);
        pwd = getpwuid(st.st_uid);
        grp = getgrgid(st.st_gid);
        printf("%s %s ", pwd->pw_name, grp->gr_name);
        printf("%5ld ", st.st_size);
        strftime(timebuf, sizeof(timebuf), "%b %d %H:%M", localtime(&st.st_mtime));
        printf("%s %s\n", timebuf, entry->d_name);
    }
    closedir(dir);
    return 0;
}
