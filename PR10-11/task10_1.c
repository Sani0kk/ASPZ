#include <stdio.h>
  #include <unistd.h>

  int main() {
      pid_t pid1 = fork(); // Перший fork
      if (pid1 == 0) {
          printf("Процес 1 (дочірній від 1-го): PID = %d, PPID = %d\n", getpid(), getppid());
      } else if (pid1 > 0) {
          pid_t pid2 = fork(); // Другий fork у батьківському
          if (pid2 == 0) {
              printf("Процес 2 (дочірній від 2-го): PID = %d, PPID = %d\n", getpid(), getppid());
          } else if (pid2 > 0) {
              printf("Процес 0 (батьківський): PID = %d, PPID = %d\n", getpid(), getppid());
          }
      }
      return 0;
  }
