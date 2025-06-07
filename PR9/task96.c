#include <stdlib.h>
int main() {
    system("ls -l ~ /usr/bin /etc");
    system("cat /etc/passwd"); 
    system("touch ~/testfile && chmod 700 ~/testfile && cat ~/testfile");
    return 0;
}
