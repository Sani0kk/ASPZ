# Практична робота №3: Обмеження ресурсів у Docker і C

## Мета роботи
Дослідити та налаштувати ліміти ресурсів (файлів, стеку, пам’яті, CPU) у Docker-контейнері та написати програми для їх демонстрації.

## Завдання 3.1: Ліміт відкритих файлів

### Опис
Експеримент із зміною софт- і хард-лімітів на кількість відкритих файлів.

### Команди
```sh
ulimit -n
ulimit -aS | grep "open files"
ulimit -aH | grep "open files"
ulimit -n 3000
ulimit -aS | grep "open files"
ulimit -aH | grep "open files"
ulimit -n 3001
ulimit -n 2000
ulimit -n
ulimit -aS | grep "open files"
ulimit -aH | grep "open files"
ulimit -n 3000
```

### З root-правами
Повторити усі команди з `sudo`.

### Скріншот
![image](https://github.com/user-attachments/assets/812ca7e8-d96f-44fa-b68c-c642b4e592d2)

## Завдання 3.3: Імітація кидання кубика

### Опис
Програма імітує кидки кубика з лімітом розміру файлу.

### Код
```c
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <sys/resource.h>

int main() {
    FILE *file = fopen("dice_rolls.txt", "w");
    if (file == NULL) {
        printf("Помилка відкриття файлу\n");
        return 1;
    }
    struct rlimit rl;
    getrlimit(RLIMIT_FSIZE, &rl);
    rl.rlim_cur = 1024;
    setrlimit(RLIMIT_FSIZE, &rl);
    srand(time(NULL));
    for (int i = 0; i < 100; i++) {
        int roll = (rand() % 6) + 1;
        if (fprintf(file, "Кидок %d: %d\n", i + 1, roll) < 0) {
            printf("Перевищено ліміт розміру файлу\n");
            break;
        }
    }
    fclose(file);
    return 0;
}
```

### Скріншот
![image](https://github.com/user-attachments/assets/b942ae2e-bbab-41f4-8138-b204898d0dc9)

## Завдання 3.4: Імітація лотереї

### Опис
Програма генерує числа для лотереї з лімітом CPU.

### Код
```c
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <sys/resource.h>

int main() {
    struct rlimit rl;
    getrlimit(RLIMIT_CPU, &rl);
    rl.rlim_cur = 1;
    setrlimit(RLIMIT_CPU, &rl);
    srand(time(NULL));
    int nums49[7], nums36[6];
    for (int i = 0; i < 7; i++) {
        nums49[i] = (rand() % 49) + 1;
        for (int j = 0; j < i; j++) if (nums49[i] == nums49[j]) i--;
    }
    for (int i = 0; i < 6; i++) {
        nums36[i] = (rand() % 36) + 1;
        for (int j = 0; j < i; j++) if (nums36[i] == nums36[j]) i--;
    }
    printf("Лотерея: 7 з 49: ");
    for (int i = 0; i < 7; i++) printf("%d ", nums49[i]);
    printf("\n6 з 36: ");
    for (int i = 0; i < 6; i++) printf("%d ", nums36[i]);
    printf("\n");
    return 0;
}
```

### Скріншот
![image](https://github.com/user-attachments/assets/b4eb04c7-f9bc-480f-9879-d317b56bf457)

## Завдання 3.5: Копіювання файлу

### Опис
Програма копіює файл із лімітом розміру.

### Код
```c
#include <stdio.h>
#include <stdlib.h>
#include <sys/resource.h>

int main(int argc, char *argv[]) {
    if (argc != 3) {
        printf("Program need two arguments\n");
        return 1;
    }
    FILE *src = fopen(argv[1], "r");
    if (src == NULL) {
        printf("Cannot open file %s for reading\n", argv[1]);
        return 1;
    }
    FILE *dest = fopen(argv[2], "w");
    if (dest == NULL) {
        printf("Cannot open file %s for writing\n", argv[2]);
        fclose(src);
        return 1;
    }
    struct rlimit rl;
    getrlimit(RLIMIT_FSIZE, &rl);
    rl.rlim_cur = 1024;
    setrlimit(RLIMIT_FSIZE, &rl);
    char buffer[1024];
    size_t bytes;
    while ((bytes = fread(buffer, 1, sizeof(buffer), src)) > 0) {
        if (fwrite(buffer, 1, bytes, dest) != bytes) {
            printf("Перевищено ліміт розміру файлу\n");
            break;
        }
    }
    fclose(src);
    fclose(dest);
    return 0;
}
```

### Скріншот
![image](https://github.com/user-attachments/assets/c7891248-c1cc-4050-9ce1-7d1cc509f2ea)

## Завдання 3.6: Обмеження стеку

### Опис
Рекурсивна програма демонструє ліміт розміру стеку.

### Код
```c
#include <stdio.h>
#include <sys/resource.h>

void recursive(int depth) {
    int x[1000];
    if (depth > 0) recursive(depth - 1);
}

int main() {
    struct rlimit rl;
    getrlimit(RLIMIT_STACK, &rl);
    rl.rlim_cur = 8192;
    setrlimit(RLIMIT_STACK, &rl);
    recursive(1000);
    printf("Стек не переповнився\n");
    return 0;
}
```

### Скріншот
![image](https://github.com/user-attachments/assets/bc21876f-6622-46ad-aa42-3ee0332edf79)

## Завдання 3.7: Обмеження віртуальної пам’яті

### Опис
Програма перевіряє ліміт віртуальної пам’яті.

### Код
```c
#include <stdio.h>
#include <stdlib.h>
#include <sys/resource.h>

int main() {
    struct rlimit rl;
    getrlimit(RLIMIT_AS, &rl);
    rl.rlim_cur = 1024 * 1024;
    setrlimit(RLIMIT_AS, &rl);
    char *data = malloc(1024 * 1024 * 2);
    if (data == NULL) {
        printf("Перевищено ліміт віртуальної пам’яті\n");
    } else {
        printf("Пам’ять виділена\n");
        free(data);
    }
    return 0;
}
```

### Скріншот
![image](https://github.com/user-attachments/assets/07c16617-21aa-4898-aad4-82ac086fa200)

## Висновок
Досліджено налаштування лімітів ресурсів у C, включаючи файли, стек, пам’ять і CPU, із відповідною обробкою перевищень.
