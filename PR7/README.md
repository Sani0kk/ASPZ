# Практична робота №7: Робота з файлами та часом

## Мета роботи
Навчитися писати програми для роботи з файлами, каталогами та вимірювання часу.

## Завдання 7.2: Імітація `ls -l`

### Опис
Показуємо файли з інформацією, як `ls -l`, без самої команди.

### Код
```c
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
```
**Пояснення**: Програма бере дані про файли з теки і показує їх, як список.

### Скріншот
![image](https://github.com/user-attachments/assets/b5ac25da-dde9-425f-914b-afdc69e9d632)

## Завдання 7.3: Проста версія `grep`

### Опис
Шукаємо рядки з певним словом у файлі.

### Код
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
        printf("Не можу відкрити файл\n");
        return 1;
    }
    char buffer[1024];
    while (fgets(buffer, sizeof(buffer), file) != NULL) {
        if (strstr(buffer, argv[2]) != NULL) {
            printf("%s", buffer);
        }
    }
    fclose(file);
    return 0;
}
```
**Пояснення**: Програма читає файл і показує рядки з заданим словом.

### Скріншот
![image](https://github.com/user-attachments/assets/c2bcffcb-db5b-4851-97d0-785efbb2e58e)

## Завдання 7.4: Спрощена версія `more`

### Опис
Показуємо файли по 20 рядків з паузами.

### Код
```c
#include <stdio.h>

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
        char buffer[1024];
        int line = 0;
        while (fgets(buffer, sizeof(buffer), file) != NULL) {
            printf("%s", buffer);
            line++;
            if (line % 20 == 0) {
                printf("Натисніть Enter для продовження...");
                getchar();
            }
        }
        fclose(file);
    }
    return 0;
}
```
**Пояснення**: Програма читає файл і зупиняється кожні 20 рядків, чекаючи натискання.

### Компіляція
```sh
gcc -Wall -o task7_4 task7_4.c
```

### Виконання
```sh
./task7_4 test.txt
```

### Скріншот
![Скріншот завдання 7.4](task7_4_screenshot.png)

## Завдання 7.5: Перелік файлів із підкаталогами

### Опис
Показуємо всі файли, включаючи підтеки.

### Код
```c
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
```
**Пояснення**: Програма проходить усі теки і показує всі файли всередині.

### Компіляція
```sh
gcc -Wall -o task7_5 task7_5.c
```

### Виконання
```sh
./task7_5
```

### Скріншот
![Скріншот завдання 7.5](task7_5_screenshot.png)

## Завдання 7.6: Перелік лише підкаталогів

### Опис
Показуємо лише теки в алфавітному порядку.

### Код
```c
#include <stdio.h>
#include <dirent.h>
#include <string.h>

int main() {
    DIR *dir = opendir(".");
    if (dir == NULL) {
        printf("Не можу відкрити теку\n");
        return 1;
    }
    struct dirent *entry;
    char dirs[100][256];
    int dirCount = 0;
    while ((entry = readdir(dir)) != NULL) {
        if (entry->d_type == DT_DIR && entry->d_name[0] != '.') {
            strcpy(dirs[dirCount++], entry->d_name);
        }
    }
    closedir(dir);
    for (int i = 0; i < dirCount - 1; i++) {
        for (int j = i + 1; j < dirCount; j++) {
            if (strcmp(dirs[i], dirs[j]) > 0) {
                char temp[256];
                strcpy(temp, dirs[i]);
                strcpy(dirs[i], dirs[j]);
                strcpy(dirs[j], temp);
            }
        }
    }
    for (int i = 0; i < dirCount; i++) {
        printf("%s\n", dirs[i]);
    }
    return 0;
}
```
**Пояснення**: Програма знаходить теки і сортує їх за алфавітом.

### Компіляція
```sh
gcc -Wall -o task7_6 task7_6.c
```

### Виконання
```sh
./task7_6
```

### Скріншот
![Скріншот завдання 7.6](task7_6_screenshot.png)

## Завдання 7.7: Зміна прав для C-файлів

### Опис
Запитуємо, чи дати дозвіл на читання C-файлам.

### Код
```c
#include <stdio.h>
#include <dirent.h>
#include <sys/stat.h>
#include <string.h>

int main() {
    DIR *dir = opendir(".");
    if (dir == NULL) {
        printf("Не можу відкрити теку\n");
        return 1;
    }
    struct dirent *entry;
    while ((entry = readdir(dir)) != NULL) {
        if (entry->d_name[0] == '.') continue;
        char *ext = strrchr(entry->d_name, '.');
        if (ext && strcmp(ext, ".c") == 0) {
            printf("Файл: %s\n", entry->d_name);
            printf("Дати дозвіл на читання іншим? (y/n): ");
            char choice;
            scanf(" %c", &choice);
            if (choice == 'y' || choice == 'Y') {
                chmod(entry->d_name, S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
                printf("Дозвіл надано\n");
            }
        }
    }
    closedir(dir);
    return 0;
}
```
**Пояснення**: Програма знаходить C-файли і запитує, чи додати дозвіл на читання.

### Компіляція
```sh
gcc -Wall -o task7_7 task7_7.c
```

### Виконання
```sh
./task7_7
```

### Скріншот
![Скріншот завдання 7.7](task7_7_screenshot.png)

## Завдання 7.8: Видалення файлів

### Опис
Запитуємо, чи видалити кожен файл.

### Код
```c
#include <stdio.h>
#include <dirent.h>
#include <unistd.h>

int main() {
    DIR *dir = opendir(".");
    if (dir == NULL) {
        printf("Не можу відкрити теку\n");
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
                printf("Файл %s видалено\n", entry->d_name);
            } else {
                printf("Помилка видалення %s\n", entry->d_name);
            }
        }
    }
    closedir(dir);
    return 0;
}
```
**Пояснення**: Програма показує файли і питає, чи видалити кожен.

### Компіляція
```sh
gcc -Wall -o task7_8 task7_8.c
```

### Виконання
```sh
./task7_8
```

### Скріншот
![Скріншот завдання 7.8](task7_8_screenshot.png)

## Завдання 7.9: Вимірювання часу

### Опис
Дізнаємося, скільки часу йде на виконання коду.

### Код
```c
#include <stdio.h>
#include <time.h>

int main() {
    clock_t start = clock();
    for (int i = 0; i < 1000000; i++) {}
    clock_t end = clock();
    double time_spent = (double)(end - start) / CLOCKS_PER_SEC * 1000;
    printf("Час виконання: %.2f мс\n", time_spent);
    return 0;
}
```
**Пояснення**: Програма вимірює час довгого циклу і показує результат.

### Компіляція
```sh
gcc -Wall -o task7_9 task7_9.c
```

### Виконання
```sh
./task7_9
```

### Скріншот
![Скріншот завдання 7.9](task7_9_screenshot.png)

## Завдання 7.10: Випадкові числа з плаваючою комою

### Опис
Генеруємо випадкові числа від 0.0 до 1.0 і до заданого числа.

### Код
```c
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main(int argc, char *argv[]) {
    srand(time(NULL));
    if (argc != 2) {
        printf("Використання: %s n\n", argv[0]);
        return 1;
    }
    double n = atof(argv[1]);
    for (int i = 0; i < 5; i++) {
        double r1 = (double)rand() / RAND_MAX;
        double r2 = r1 * n;
        printf("0.0-1.0: %.2f, 0.0-%.2f: %.2f\n", r1, n, r2);
    }
    return 0;
}
```
**Пояснення**: Програма створює 5 випадкових чисел у двох діапазонах.

### Компіляція
```sh
gcc -Wall -o task7_10 task7_10.c
```

### Виконання
```sh
./task7_10 10
```

### Скріншот
![Скріншот завдання 7.10](task7_10_screenshot.png)

## Завдання 7.11: Аналіз змінених файлів

### Опис
Шукаємо файли, змінені за останні 7 днів.

### Код
```c
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
```
**Пояснення**: Програма перевіряє, які файли змінювалися тиждень тому, і показує їх.

### Компіляція
```sh
gcc -Wall -o task7_11 task7_11.c
```

### Виконання
```sh
./task7_11
```

### Скріншот
![Скріншот завдання 7.11](task7_11_screenshot.png)

## Висновок
Дізналися, як працювати з файлами, теками, часом і командами в C.
