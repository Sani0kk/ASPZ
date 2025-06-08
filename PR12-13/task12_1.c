#include <stdio.h>
  #include <stdlib.h>
  #include <signal.h>
  #include <unistd.h>
  #include <sys/mman.h>
  #include <fcntl.h>

  void sigbus_handler(int sig, siginfo_t *info, void *context) {
      if (info->si_code == BUS_ADRERR) {
          printf("Помилка SIGBUS: Невірна адреса (фізична пам’ять), адреса: %p\n", info->si_addr);
      } else if (info->si_code == BUS_OBJERR) {
          printf("Помилка SIGBUS: Помилка об’єкта (mmap), адреса: %p\n", info->si_addr);
      } else {
          printf("Невідома помилка SIGBUS, адреса: %p\n", info->si_addr);
      }
      exit(1);
  }

  int main() {
      struct sigaction sa;
      sa.sa_sigaction = sigbus_handler;
      sa.sa_flags = SA_SIGINFO;
      sigemptyset(&sa.sa_mask);
      if (sigaction(SIGBUS, &sa, NULL) == -1) {
          perror("Помилка встановлення обробника");
          return 1;
      }

      int fd = open("test.txt", O_RDWR | O_CREAT | O_TRUNC, 0644);
      if (fd == -1) {
          perror("Помилка відкриття файлу");
          return 1;
      }
      write(fd, "123", 3);
      void *addr = mmap(NULL, 4096, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);
      if (addr == MAP_FAILED) {
          perror("Помилка mmap");
          close(fd);
          return 1;
      }
      printf("Відображено: %p\n", addr);
      char *p = (char *)addr;
      p[0] = 'A'; // Доступ до відображеної пам’яті — нормально
      printf("Записано: %c\n", p[0]);
      p += 4096; // Перехід за межі відображеної області
      *p = 'B';  // Викликає SIGBUS (BUS_OBJERR)
      close(fd);
      return 0;
  }
