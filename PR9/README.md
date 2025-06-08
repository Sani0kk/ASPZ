# Практична робота №9: Управління доступом і файлами

## Мета роботи
Дізнатися, як управляти доступом до файлів, перевіряти облікові записи та виконувати операції від імені різних користувачів.

## Завдання 9.1: Читання /etc/passwd через getent
### Опис
Програма зчитує `/etc/passwd` через `getent passwd`, шукає звичайних користувачів (UID > 1000, крім вас) і показує їх кількість.
### Код
```c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

int main() {
    FILE *pipe = popen("getent passwd", "r");
    if (pipe == NULL) {
        perror("Помилка виконання popen");
        exit(EXIT_FAILURE);
    }

    char line[256];
    int current_uid = getuid();
    int normal_users = 0;

    while (fgets(line, sizeof(line), pipe) != NULL) {
        int uid;
        if (sscanf(line, "%*[^:]:%*[^:]:%d", &uid) == 1 && uid > 1000 && uid != current_uid) {
            normal_users++;
            printf("Знайдено користувача з UID: %d\n", uid);
        }
    }

    pclose(pipe);
    printf("Кількість звичайних користувачів (крім вас): %d\n", normal_users);
    return 0;
}
```
### Скріншот виконання
![image](https://github.com/user-attachments/assets/4a63420d-e839-418b-a459-1d5c22dbf00e)

## Завдання 9.2: Виконання cat /etc/shadow від імені адміністратора
### Опис
Програма намагається стати root через `setuid(0)` і виводить вміст `/etc/shadow`. Потрібен доступ root або налаштування sudo.
### Код
```c
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main() {
    if (setuid(0) == -1) {
        fprintf(stderr, "Помилка: не вдалося отримати права root. Перевірте sudo.\n");
        exit(EXIT_FAILURE);
    }
    if (getuid() != 0) {
        fprintf(stderr, "Помилка: немає доступу до root.\n");
        exit(EXIT_FAILURE);
    }

    FILE *fp = popen("cat /etc/shadow", "r");
    if (fp == NULL) {
        perror("Помилка виконання popen");
        exit(EXIT_FAILURE);
    }

    char buffer[256];
    while (fgets(buffer, sizeof(buffer), fp) != NULL) {
        printf("%s", buffer);
    }

    pclose(fp);
    return 0;
}
```
### Скріншот виконання
![Скріншот завдання 9.2](task9_2_screenshot.png)

## Завдання 9.3: Копіювання файлу від root у домашній каталог
### Опис
Програма створює `user_temp.txt`, копіює його як root у `/home/san/copied_temp.txt`, потім пробує змінити/видалити його як звичайний користувач (без успіху).
### Код
```c
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>

int main() {
    const char *source = "user_temp.txt";
    const char *dest = "/home/san/copied_temp.txt";

    int fd = open(source, O_CREAT | O_WRONLY, 0644);
    if (fd < 0) {
        perror("Помилка створення файлу");
        exit(EXIT_FAILURE);
    }
    write(fd, "Тестовий вміст", 14);
    close(fd);

    if (setuid(0) == -1) {
        perror("Помилка переходу до root");
        exit(EXIT_FAILURE);
    }
    if (getuid() != 0) {
        fprintf(stderr, "Немає root-доступу.\n");
        exit(EXIT_FAILURE);
    }

    if (link(source, dest) == -1) {
        perror("Помилка копіювання");
        exit(EXIT_FAILURE);
    }
    printf("Файл скопійовано до %s.\n", dest);

    setuid(getuid());
    fd = open(dest, O_WRONLY);
    if (fd < 0) {
        printf("Помилка запису: %s (немає прав).\n", strerror(errno));
    } else {
        write(fd, "Спроба зміни", 12);
        close(fd);
    }

    if (unlink(dest) == -1) {
        printf("Помилка видалення: %s (немає прав).\n", strerror(errno));
    } else {
        printf("Файл видалено.\n");
    }

    return 0;
}
```
### Скріншот виконання
![Скріншот завдання 9.3](task9_3_screenshot.png)

## Завдання 9.4: Перевірка стану облікового запису
### Опис
Програма показує ваше ім’я через `whoami` і деталі облікового запису (включаючи групи) через `id`.
### Код
```c
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main() {
    FILE *cmd = popen("whoami", "r");
    if (cmd == NULL) {
        perror("Помилка виконання whoami");
        exit(EXIT_FAILURE);
    }
    char name[256];
    fgets(name, sizeof(name), cmd);
    printf("whoami: %s", name);
    pclose(cmd);

    cmd = popen("id", "r");
    if (cmd == NULL) {
        perror("Помилка виконання id");
        exit(EXIT_FAILURE);
    }
    printf("id: ");
    char id_line[256];
    while (fgets(id_line, sizeof(id_line), cmd) != NULL) {
        printf("%s", id_line);
    }
    pclose(cmd);

    return 0;
}
```
### Скріншот виконання
![Скріншот завдання 9.4](task9_4_screenshot.png)

## Завдання 9.5: Створення та зміна тимчасового файлу
### Опис
Програма створює `test_temp.txt`, змінює його права як root на 0600, а потім перевіряє доступ як звичайний користувач (доступ буде заборонено).
### Код
```c
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>

int main() {
    const char *temp_file = "test_temp.txt";
    int fd = open(temp_file, O_CREAT | O_WRONLY, 0644);
    if (fd < 0) {
        perror("Помилка створення файлу");
        exit(EXIT_FAILURE);
    }
    write(fd, "Тест", 4);
    close(fd);

    if (setuid(0) == -1) {
        perror("Помилка переходу до root");
        exit(EXIT_FAILURE);
    }
    if (getuid() != 0) {
        fprintf(stderr, "Немає root-доступу.\n");
        exit(EXIT_FAILURE);
    }

    if (chown(temp_file, getuid(), getgid()) == -1) {
        perror("Помилка chown");
    }
    if (chmod(temp_file, 0600) == -1) {
        perror("Помилка chmod");
    }

    setuid(getuid());
    fd = open(temp_file, O_RDWR);
    if (fd >= 0) {
        printf("Доступ до файлу для читання/запису.\n");
        close(fd);
    } else {
        printf("Немає доступу: %s\n", strerror(errno));
    }

    return 0;
}
```
### Скріншот виконання
![Скріншот завдання 9.5](task9_5_screenshot.png)

## Завдання 9.6: Виконання ls -l для різних каталогів
### Опис
Програма показує права доступу до файлів у `/home/san`, `/usr/bin` і `/etc` за допомогою `ls -l`, а потім пробує "прочитати" ці каталоги, щоб показати обмеження доступу.
### Код
```c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
    const char *dirs[] = {"/home/san", "/usr/bin", "/etc", NULL};
    for (int i = 0; dirs[i] != NULL; i++) {
        char cmd[128];
        snprintf(cmd, sizeof(cmd), "ls -l %s", dirs[i]);
        FILE *ls_pipe = popen(cmd, "r");
        if (ls_pipe == NULL) {
            perror("Помилка виконання ls");
            continue;
        }
        printf("Права для %s:\n", dirs[i]);
        char buf[256];
        while (fgets(buf, sizeof(buf), ls_pipe) != NULL) {
            printf("%s", buf);
        }
        pclose(ls_pipe);

        FILE *cat_pipe = popen("cat", "w");
        if (cat_pipe != NULL) {
            fprintf(cat_pipe, "Спроба читання %s\n", dirs[i]);
            pclose(cat_pipe);
        }
    }
    return 0;
}
```
### Скріншот виконання
![Скріншот завдання 9.6](task9_6_screenshot.png)

## Завдання 9.7: Читання файлу без прав
### Опис
Програма створює `no_access.txt` без прав (0000) і пробує його прочитати, показуючи, що доступ заборонено.
### Код
```c
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>

int main() {
    const char *file = "no_access.txt";
    int fd = open(file, O_CREAT | O_WRONLY, 0000);
    if (fd < 0) {
        perror("Помилка створення файлу");
        exit(EXIT_FAILURE);
    }
    write(fd, "Конфіденційні дані", 18);
    close(fd);

    fd = open(file, O_RDONLY);
    if (fd < 0) {
        printf("Читання неможливе: %s\n", strerror(errno));
    } else {
        char buf[256];
        read(fd, buf, sizeof(buf));
        printf("Вміст: %s\n", buf);
        close(fd);
    }

    return 0;
}
```
### Скріншот виконання
![Скріншот завдання 9.7](task9_7_screenshot.png)

## Висновок
Дізналися, як управляти доступом до файлів, перевіряти користувачів і демонструвати поведінку прав на FreeBSD.
