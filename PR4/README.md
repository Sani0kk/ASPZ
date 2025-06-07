# Практична робота №4: Дослідження `malloc` і `realloc`

## Мета роботи
Дослідити поведінку функцій `malloc`, `realloc` і `reallocarray` у різних сценаріях, включаючи розміри, від’ємні аргументи, нульові значення та багатопоточність.

## Завдання 4.1: Максимальний обсяг пам’яті для `malloc`

### Опис
Перевірка максимального обсягу пам’яті, який можна виділити. Теоретичний ліміт 2^64, але на практиці ~8 ексабайт через накладні витрати.

### Код
```c
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

int main() {
    size_t max_size = SIZE_MAX;
    printf("Максимальне значення size_t: %zu байтів\n", max_size);
    void *ptr = malloc(max_size);
    if (ptr == NULL) {
        printf("malloc(%zu) повернув NULL (пам’ять не виділена)\n", max_size);
    } else {
        printf("Пам’ять успішно виділена: %p\n", ptr);
        free(ptr);
    }
    return 0;
}
```

### Компіляція
```sh
gcc -Wall -o task4_1 task4_1.c
```

### Виконання
```sh
./task4_1
```

### Скріншот
![Скріншот завдання 4.1](task4_1_screenshot.png)

## Завдання 4.2: Від’ємний аргумент для `malloc`

### Опис
Перевірка поведінки при від’ємному аргументі через переповнення.

### Код
```c
#include <stdio.h>
#include <stdlib.h>

int main() {
    int xa = -2, xb = 3;
    int num = xa * xb;
    printf("num = %d\n", num);
    void *ptr = malloc(num);
    if (ptr == NULL) {
        printf("malloc(%d) повернув NULL\n", num);
    } else {
        printf("Пам’ять виділена: %p\n", ptr);
        free(ptr);
    }
    return 0;
}
```

### Компіляція
```sh
gcc -Wall -o task4_2 task4_2.c
```

### Виконання
```sh
./task4_2
```

### Скріншот
![Скріншот завдання 4.2](task4_2_screenshot.png)

## Завдання 4.3: Поведінка `malloc(0)`

### Опис
Перевірка повернення `NULL` або валідного вказівника при `malloc(0)`.

### Код
```c
#include <stdio.h>
#include <stdlib.h>

int main() {
    void *ptr = malloc(0);
    if (ptr == NULL) {
        printf("malloc(0) повернув NULL\n");
    } else {
        printf("malloc(0) повернув вказівник: %p\n", ptr);
        free(ptr);
    }
    return 0;
}
```

### Компіляція
```sh
gcc -Wall -o task4_3 task4_3.c
```

### Виконання
```sh
./task4_3
ltrace ./task4_3
```

### Скріншот
![Скріншот завдання 4.3](task4_3_screenshot.png)

## Завдання 4.4: Помилки у коді з `free`

### Опис
Демонстрація проблеми повторного `free` і правильного варіанту.

### Неправильний код
```c
#include <stdio.h>
#include <stdlib.h>

int main() {
    void *ptr = NULL;
    int i = 0;
    while (i < 3) {
        if (!ptr) {
            ptr = malloc(100);
            if (ptr == NULL) {
                printf("Помилка виділення пам’яті\n");
                return 1;
            }
        }
        printf("Використання ptr: %p\n", ptr);
        free(ptr);
        i++;
    }
    return 0;
}
```

### Правильний код
```c
#include <stdio.h>
#include <stdlib.h>

int main() {
    void *ptr = NULL;
    int i = 0;
    while (i < 3) {
        if (!ptr) {
            ptr = malloc(100);
            if (ptr == NULL) {
                printf("Помилка виділення пам’яті\n");
                return 1;
            }
        }
        printf("Використання ptr: %p\n", ptr);
        i++;
    }
    free(ptr);
    return 0;
}
```

### Компіляція
```sh
gcc -Wall -o task4_4 task4_4.c
gcc -Wall -o task4_4_correct task4_4_correct.c
```

### Виконання
```sh
./task4_4
./task4_4_correct
```

### Скріншот
![Скріншот завдання 4.4](task4_4_screenshot.png)

## Завдання 4.5: Невдале виділення `realloc`

### Опис
Демонстрація поведінки `realloc` при невдалому виділенні.

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
    void *ptr = malloc(512 * 1024);
    if (ptr == NULL) {
        printf("Помилка початкового malloc\n");
        return 1;
    }
    void *new_ptr = realloc(ptr, 2 * 1024 * 1024);
    if (new_ptr == NULL) {
        printf("realloc не зміг виділити 2 МБ, ptr збережено: %p\n", ptr);
    } else {
        printf("realloc успішно: %p\n", new_ptr);
        ptr = new_ptr;
    }
    free(ptr);
    return 0;
}
```

### Компіляція
```sh
gcc -Wall -o task4_5 task4_5.c
```

### Виконання
```sh
./task4_5
```

### Скріншот
![Скріншот завдання 4.5](task4_5_screenshot.png)

## Завдання 4.6: `realloc` із `NULL` або `0`

### Опис
Перевірка поведінки `realloc` при `NULL` або розмірі 0.

### Код
```c
#include <stdio.h>
#include <stdlib.h>

int main() {
    void *ptr1 = realloc(NULL, 100);
    void *ptr2 = realloc(ptr1, 0);
    if (ptr1 == NULL) {
        printf("ptr1 NULL після realloc(NULL, 100)\n");
    } else {
        printf("ptr1: %p\n", ptr1);
        free(ptr1);
    }
    if (ptr2 == NULL) {
        printf("ptr2 NULL після realloc(..., 0)\n");
    } else {
        printf("ptr2: %p\n", ptr2);
    }
    return 0;
}
```

### Компіляція
```sh
gcc -Wall -o task4_6 task4_6.c
```

### Виконання
```sh
./task4_6
```

### Скріншот
![Скріншот завдання 4.6](task4_6_screenshot.png)

## Завдання 4.7: Використання `reallocarray`

### Опис
Переписування коду з `reallocarray`.

### Код
```c
#include <stdio.h>
#include <stdlib.h>

int main() {
    struct sbar {
        int data;
    };
    struct sbar *ptr = calloc(1000, sizeof(struct sbar));
    if (ptr == NULL) {
        printf("Помилка calloc\n");
        return 1;
    }
    struct sbar *newptr = reallocarray(ptr, 500, sizeof(struct sbar));
    if (newptr == NULL) {
        printf("Помилка reallocarray\n");
        free(ptr);
        return 1;
    }
    printf("Успішно перевиділено: %p\n", newptr);
    free(newptr);
    return 0;
}
```

### Компіляція
```sh
gcc -Wall -o task4_7 task4_7.c
```

### Виконання
```sh
./task4_7
ltrace ./task4_7
```

### Скріншот
![Скріншот завдання 4.7](task4_7_screenshot.png)

## Завдання 4.8: `malloc` у багатопоточному середовищі

### Опис
Демонстрація роботи `malloc` у кількох потоках.

### Код
```c
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

void *thread_func(void *arg) {
    void *ptr = malloc(100);
    if (ptr == NULL) {
        printf("Потік: Помилка malloc\n");
    } else {
        printf("Потік %ld: Пам’ять виділено: %p\n", (long)arg, ptr);
    }
    sleep(1);
    free(ptr);
    return NULL;
}

int main() {
    pthread_t threads[5];
    for (long i = 0; i < 5; i++) {
        pthread_create(&threads[i], NULL, thread_func, (void *)i);
    }
    for (int i = 0; i < 5; i++) {
        pthread_join(threads[i], NULL);
    }
    return 0;
}
```

### Компіляція
```sh
gcc -Wall -o task4_8 task4_8.c -pthread
```

### Виконання
```sh
./task4_8
```

### Скріншот
![Скріншот завдання 4.8](task4_8_screenshot.png)

## Висновок
Досліджено поведінку `malloc`, `realloc` і `reallocarray` у різних сценаріях, включаючи розміри, помилки та багатопоточність.
