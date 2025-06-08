# Практична робота №7: Робота з файлами та каталогами

## Мета роботи
Дізнатися, як працювати з файлами, каталогами, правами доступу, вимірюванням часу та генерацією випадкових чисел у мові програмування C на операційній системі FreeBSD.

## Завдання

### Завдання 7.2: Імітація `ls -l` у C

#### Опис
Програма відображає список файлів у поточному каталозі із деталями (права доступу, власник, група, розмір, час модифікації).

#### Код
```c
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
```

#### Скріншот
![image](https://github.com/user-attachments/assets/9d5c5f23-f09a-4f30-a9ce-33f49b1bb0c3)

#### Пояснення
Програма імітує поведінку `ls -l` без використання самої команди.

---

### Завдання 7.3: Проста версія `grep`

#### Опис
Програма шукає та виводить рядки з файлу, що містять задане слово.

#### Код
```c
#include <stdio.h>
#include <string.h>

int main(int argc, char *argv[]) {
    if (argc != 3) {
        printf("Використання: %s файл слово\n", argv[0]);
        return 1;
    }

    FILE *file = fopen(argv[1], "r");
    if (file == NULL) {
        perror("Помилка відкриття файлу");
        return 1;
    }

    char line[256];
    while (fgets(line, sizeof(line), file) != NULL) {
        if (strstr(line, argv[2]) != NULL) {
            printf("%s", line);
        }
    }

    fclose(file);
    return 0;
}
```

#### Компіляція
```sh
gcc -Wall -o task7_3 task7_3.c
```

#### Виконання
```sh
./task7_3 test.txt слово
```

#### Очікуваний результат
- Приклад:  
  ```
  привіт світ
  ```

#### Скріншот
- ![Скріншот виконання завдання 7.3](task7_3_screenshot.png)

#### Пояснення
Програма імітує базову поведінку `grep`.

---

### Завдання 7.4: Спрощена версія `more`

#### Опис
Програма виводить вміст файлів із паузою кожні 20 рядків.

#### Код
```c
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
    if (argc < 2) {
        printf("Використання: %s файл1 [файл2 ...]\n", argv[0]);
        return 1;
    }

    for (int i = 1; i < argc; i++) {
        FILE *file = fopen(argv[i], "r");
        if (file == NULL) {
            printf("Не можу відкрити %s\n", argv[i]);
            continue;
        }

        char line[256];
        int count = 0;
        while (fgets(line, sizeof(line), file) != NULL) {
            printf("%s", line);
            count++;
            if (count % 20 == 0) {
                printf("Натисніть Enter для продовження...");
                getchar();
            }
        }

        fclose(file);
    }

    return 0;
}
```

#### Компіляція
```sh
gcc -Wall -o task7_4 task7_4.c
```

#### Виконання
```sh
./task7_4 test.txt
```

#### Очікуваний результат
- Виводить вміст із паузою:  
  ```
  Натисніть Enter для продовження...
  ```

#### Скріншот
- ![Скріншот виконання завдання 7.4](task7_4_screenshot.png)

#### Пояснення
Програма паузить виведення кожні 20 рядків.

---

### Завдання 7.5: Рекурсивний перелік файлів

#### Опис
Програма виводить усі файли в поточному каталозі та підкаталогах.

#### Код
```c
#include <stdio.h>
#include <dirent.h>
#include <string.h>

void list_files(const char *path) {
    DIR *dir = opendir(path);
    if (dir == NULL) {
        perror("Помилка відкриття каталогу");
        return;
    }

    struct dirent *entry;
    while ((entry = readdir(dir)) != NULL) {
        if (entry->d_name[0] == '.') continue;
        char full_path[512];
        snprintf(full_path, sizeof(full_path), "%s/%s", path, entry->d_name);
        printf("%s\n", full_path);
        if (entry->d_type == DT_DIR) {
            list_files(full_path);
        }
    }

    closedir(dir);
}

int main() {
    list_files(".");
    return 0;
}
```

#### Компіляція
```sh
gcc -Wall -o task7_5 task7_5.c
```

#### Виконання
```sh
./task7_5
```

#### Очікуваний результат
- Приклад:  
  ```
  ./file.txt
  ./subdir/subfile.txt
  ```

#### Скріншот
- ![Скріншот виконання завдання 7.5](task7_5_screenshot.png)

#### Пояснення
Програма рекурсивно обходить усі підкаталоги.

---

### Завдання 7.6: Перелік підкаталогів в алфавітному порядку

#### Опис
Програма виводить підкаталоги в алфавітному порядку.

#### Код
```c
#include <stdio.h>
#include <dirent.h>
#include <string.h>
#include <stdlib.h>

int compare(const void *a, const void *b) {
    return strcmp(*(const char **)a, *(const char **)b);
}

int main() {
    DIR *dir = opendir(".");
    if (dir == NULL) {
        perror("Помилка відкриття каталогу");
        return 1;
    }

    struct dirent *entry;
    char *dirs[100];
    int dir_count = 0;
    while ((entry = readdir(dir)) != NULL) {
        if (entry->d_type == DT_DIR && entry->d_name[0] != '.') {
            dirs[dir_count++] = strdup(entry->d_name);
        }
    }
    closedir(dir);

    qsort(dirs, dir_count, sizeof(char *), compare);
    for (int i = 0; i < dir_count; i++) {
        printf("%s\n", dirs[i]);
        free(dirs[i]);
    }

    return 0;
}
```

#### Компіляція
```sh
gcc -Wall -o task7_6 task7_6.c
```

#### Виконання
```sh
./task7_6
```

#### Очікуваний результат
- Приклад:  
  ```
  dir1
  dir2
  subdir
  ```

#### Скріншот
- ![Скріншот виконання завдання 7.6](task7_6_screenshot.png)

#### Пояснення
Сортування підкаталогів виконується за допомогою `qsort`.

---

### Завдання 7.7: Зміна прав читання для файлів C

#### Опис
Програма інтерактивно змінює права читання для `.c` файлів.

#### Код
```c
#include <stdio.h>
#include <dirent.h>
#include <string.h>
#include <sys/stat.h>

int main() {
    DIR *dir = opendir(".");
    if (dir == NULL) {
        perror("Помилка відкриття каталогу");
        return 1;
    }

    struct dirent *entry;
    while ((entry = readdir(dir)) != NULL) {
        if (strstr(entry->d_name, ".c") != NULL) {
            printf("Файл: %s\n", entry->d_name);
            printf("Надати дозвіл на читання іншим? (y/n): ");
            char choice;
            scanf(" %c", &choice);
            if (choice == 'y' || choice == 'Y') {
                struct stat fileStat;
                stat(entry->d_name, &fileStat);
                chmod(entry->d_name, fileStat.st_mode | S_IROTH);
                printf("Дозвіл надано.\n");
            }
        }
    }

    closedir(dir);
    return 0;
}
```

#### Компіляція
```sh
gcc -Wall -o task7_7 task7_7.c
```

#### Виконання
```sh
./task7_7
```

#### Очікуваний результат
- Приклад:  
  ```
  Файл: task7_1.c
  Надати дозвіл на читання іншим? (y/n): y
  Дозвіл надано.
  ```

#### Скріншот
- ![Скріншот виконання завдання 7.7](task7_7_screenshot.png)

#### Пояснення
Програма дозволяє інтерактивно надавати права.

---

### Завдання 7.8: Інтерактивне видалення файлів

#### Опис
Програма запитує, чи видалити кожен файл у поточному каталозі.

#### Код
```c
#include <stdio.h>
#include <dirent.h>
#include <unistd.h>

int main() {
    DIR *dir = opendir(".");
    if (dir == NULL) {
        perror("Помилка відкриття каталогу");
        return 1;
    }

    struct dirent *entry;
    while ((entry = readdir(dir)) != NULL) {
        if (entry->d_name[0] == '.') continue;
        printf("Видалити %s? (y/n): ", entry->d_name);
        char choice;
        scanf(" %c", &choice);
        if (choice == 'y' || choice == 'Y') {
            if (unlink(entry->d_name) == 0) {
                printf("Файл %s видалено.\n", entry->d_name);
            } else {
                printf("Помилка видалення %s\n", entry->d_name);
            }
        }
    }

    closedir(dir);
    return 0;
}
```

#### Компіляція
```sh
gcc -Wall -o task7_8 task7_8.c
```

#### Виконання
```sh
./task7_8
```

#### Очікуваний результат
- Приклад:  
  ```
  Видалити file.txt? (y/n): y
  Файл file.txt видалено.
  ```

#### Скріншот
- ![Скріншот виконання завдання 7.8](task7_8_screenshot.png)

#### Пояснення
Програма дозволяє інтерактивно видаляти файли.

---

### Завдання 7.9: Вимірювання часу виконання коду

#### Опис
Програма вимірює час виконання фрагмента коду в мілісекундах.

#### Код
```c
#include <stdio.h>
#include <time.h>

int main() {
    clock_t start = clock();
    for (int i = 0; i < 1000000; i++) {
        // Імітація обчислень
    }
    clock_t end = clock();
    double time_spent = (double)(end - start) / CLOCKS_PER_SEC * 1000;
    printf("Час виконання: %.2f мс\n", time_spent);
    return 0;
}
```

#### Компіляція
```sh
gcc -Wall -o task7_9 task7_9.c
```

#### Виконання
```sh
./task7_9
```

#### Очікуваний результат
- Приклад:  
  ```
  Час виконання: 10.50 мс
  ```

#### Скріншот
- ![Скріншот виконання завдання 7.9](task7_9_screenshot.png)

#### Пояснення
Програма вимірює час циклу.

---

### Завдання 7.10: Генерація випадкових чисел

#### Опис
Програма генерує випадкові числа в діапазонах від 0.0 до 1.0 та від 0.0 до n.

#### Код
```c
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main(int argc, char *argv[]) {
    if (argc != 2) {
        printf("Використання: %s n\n", argv[0]);
        return 1;
    }

    double n = atof(argv[1]);
    srand(time(NULL));

    for (int i = 0; i < 5; i++) {
        double r1 = (double)rand() / RAND_MAX;
        double r2 = r1 * n;
        printf("0.0-1.0: %.2f, 0.0-%.2f: %.2f\n", r1, n, r2);
    }

    return 0;
}
```

#### Компіляція
```sh
gcc -Wall -o task7_10 task7_10.c
```

#### Виконання
```sh
./task7_10 10
```

#### Очікуваний результат
- Приклад:  
  ```
  0.0-1.0: 0.45, 0.0-10.00: 4.50
  0.0-1.0: 0.72, 0.0-10.00: 7.20
  ```

#### Скріншот
- ![Скріншот виконання завдання 7.10](task7_10_screenshot.png)

#### Пояснення
Програма генерує випадкові числа з унікальним початковим значенням.

---

### Завдання 7.11: Аналіз файлів, змінених за останні 7 днів

#### Опис
Програма виводить файли, змінені за останні 7 днів.

#### Код
```c
#include <stdio.h>
#include <dirent.h>
#include <sys/stat.h>
#include <time.h>

int main() {
    DIR *dir = opendir(".");
    if (dir == NULL) {
        perror("Помилка відкриття каталогу");
        return 1;
    }

    time_t now = time(NULL);
    time_t week_ago = now - 7 * 24 * 3600;

    struct dirent *entry;
    while ((entry = readdir(dir)) != NULL) {
        if (entry->d_name[0] == '.') continue;
        struct stat fileStat;
        if (stat(entry->d_name, &fileStat) == -1) continue;
        if (fileStat.st_mtime > week_ago) {
            char time_buf[20];
            strftime(time_buf, sizeof(time_buf), "%Y-%m-%d %H:%M:%S", localtime(&fileStat.st_mtime));
            printf("%s (змінено: %s)\n", entry->d_name, time_buf);
        }
    }

    closedir(dir);
    return 0;
}
```

#### Компіляція
```sh
gcc -Wall -o task7_11 task7_11.c
```

#### Виконання
```sh
./task7_11
```

#### Очікуваний результат
- Приклад:  
  ```
  file.txt (змінено: 2025-06-08 13:00:00)
  ```

#### Скріншот
- ![Скріншот виконання завдання 7.11](task7_11_screenshot.png)

#### Пояснення
Програма аналізує час модифікації файлів.

---

## Висновок
Практична робота дозволила дослідити основи роботи з файлами, каталогами, правами доступу, вимірюванням часу та генерацією випадкових чисел у C на FreeBSD.
