# Практична робота №4: Дослідження `malloc` і `realloc`

## Мета роботи
Дізнатися, як працюють функції `malloc`, `realloc` і `reallocarray` у різних ситуаціях, наприклад, із розмірами, помилками чи кількома потоками.

## Завдання 4.1: Максимальний обсяг пам’яті для `malloc`

### Опис
Перевіряємо, скільки пам’яті можна виділити за один раз. Теоретично до 16 ексабайт, але на практиці менше через обмеження системи.

### Код
```c
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

int main() {
    size_t max_size = SIZE_MAX; // Беремо максимальний розмір, який може бути
    printf("Максимальне значення size_t: %zu байтів\n", max_size);
    void *ptr = malloc(max_size); // Спроба виділити максимум
    if (ptr == NULL) {
        printf("malloc(%zu) повернув NULL (пам’ять не виділена)\n", max_size);
    } else {
        printf("Пам’ять успішно виділена: %p\n", ptr);
        free(ptr); // Звільняємо, якщо вдалося
    }
    return 0;
}
```
**Пояснення**: Ця програма показує, який найбільший розмір пам’яті можна попросити, і перевіряє, чи вдасться його виділити. Зазвичай система каже "ні".

### Скріншот
![image](https://github.com/user-attachments/assets/fa96e242-af12-4c6b-9c71-d6ba11d8c293)

## Завдання 4.2: Від’ємний аргумент для `malloc`

### Опис
Дивимося, що відбувається, якщо дати `malloc` від’ємне число через множення.

### Код
```c
#include <stdio.h>
#include <stdlib.h>

int main() {
    int xa = -2, xb = 3; // Два числа для множення
    int num = xa * xb; // Множимо, отримуємо від’ємне
    printf("num = %d\n", num);
    void *ptr = malloc(num); // Спроба виділити з від’ємним числом
    if (ptr == NULL) {
        printf("malloc(%d) повернув NULL\n", num);
    } else {
        printf("Пам’ять виділена: %p\n", ptr);
        free(ptr);
    }
    return 0;
}
```
**Пояснення**: Програма множить числа, отримує від’ємний результат, і `malloc` не може з ним працювати, тому повертає "нічого".

### Скріншот
![image](https://github.com/user-attachments/assets/67b0dcb9-8f75-4061-8cbd-5c53b400059c)

## Завдання 4.3: Поведінка `malloc(0)`

### Опис
Перевіряємо, що робить `malloc`, якщо попросити 0 байтів.

### Код
```c
#include <stdio.h>
#include <stdlib.h>

int main() {
    void *ptr = malloc(0); // Просимо 0 байтів
    if (ptr == NULL) {
        printf("malloc(0) повернув NULL\n");
    } else {
        printf("malloc(0) повернув вказівник: %p\n", ptr);
        free(ptr); // Звільняємо, якщо є
    }
    return 0;
}
```
**Пояснення**: Програма питає 0 байтів, і система може повернути "нічого" або якийсь адресу, яку можна звільнити.

### Скріншот
![image](https://github.com/user-attachments/assets/1c5e36d9-acfd-4c05-b603-cf5abd773a01)

## Завдання 4.4: Помилки у коді з `free`

### Опис
Показуємо проблему, коли пам’ять звільняють занадто багато разів, і як це виправити.

### Неправильний код
```c
#include <stdio.h>
#include <stdlib.h>

int main() {
    void *ptr = NULL;
    int i = 0;
    while (i < 3) {
        if (!ptr) {
            ptr = malloc(100); // Беремо пам’ять
            if (ptr == NULL) {
                printf("Помилка виділення пам’яті\n");
                return 1;
            }
        }
        printf("Використання ptr: %p\n", ptr);
        free(ptr); // Звільняємо щоразу, що погано
        i++;
    }
    return 0;
}
```
**Пояснення**: Ця версія звільняє пам’ять кілька разів, що ламає програму.

### Правильний код
```c
#include <stdio.h>
#include <stdlib.h>

int main() {
    void *ptr = NULL;
    int i = 0;
    while (i < 3) {
        if (!ptr) {
            ptr = malloc(100); // Беремо пам’ять
            if (ptr == NULL) {
                printf("Помилка виділення пам’яті\n");
                return 1;
            }
        }
        printf("Використання ptr: %p\n", ptr);
        i++;
    }
    free(ptr); // Звільняємо лише один раз
    return 0;
}
```
**Пояснення**: Тут пам’ять беруть один раз і звільняють лише в кінці, що правильно.

### Скріншот
![image](https://github.com/user-attachments/assets/8097766f-d08d-422e-8eeb-7b6f1a8045c8)

## Завдання 4.5: Невдале виділення `realloc`

### Опис
Дивимося, що відбувається, якщо `realloc` не може збільшити пам’ять.

### Код
```c
#include <stdio.h>
#include <stdlib.h>
#include <sys/resource.h>

int main() {
    struct rlimit rl;
    getrlimit(RLIMIT_AS, &rl);
    rl.rlim_cur = 1024 * 1024; // Обмежуємо до 1 МБ
    setrlimit(RLIMIT_AS, &rl);
    void *ptr = malloc(512 * 1024); // Беремо 0.5 МБ
    if (ptr == NULL) {
        printf("Помилка початкового malloc\n");
        return 1;
    }
    void *new_ptr = realloc(ptr, 2 * 1024 * 1024); // Хочемо 2 МБ
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
**Пояснення**: Програма просить збільшити пам’ять, але якщо не виходить, зберігає старе значення.

### Скріншот
![image](https://github.com/user-attachments/assets/cb525b1b-3149-4825-8841-52d42bfb4193)

## Завдання 4.6: `realloc` із `NULL` або `0`

### Опис
Перевіряємо, що робить `realloc`, якщо дати `NULL` або 0.

### Код
```c
#include <stdio.h>
#include <stdlib.h>

int main() {
    void *ptr1 = realloc(NULL, 100); // Як новий malloc
    void *ptr2 = realloc(ptr1, 0);   // Як free
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
**Пояснення**: `NULL` дає нову пам’ять, а 0 звільняє її і повертає "нічого".

### Скріншот
![image](https://github.com/user-attachments/assets/6e90b9f3-24bc-46fc-b37f-a19123904893)

## Завдання 4.7: Використання `reallocarray`

### Опис
Переписуємо код із `reallocarray` для безпечного зміни розміру.

### Код
```c
#include <stdio.h>
#include <stdlib.h>

int main() {
    struct sbar {
        int data;
    };
    struct sbar *ptr = calloc(1000, sizeof(struct sbar)); // Беремо 1000 елементів
    if (ptr == NULL) {
        printf("Помилка calloc\n");
        return 1;
    }
    struct sbar *newptr = reallocarray(ptr, 500, sizeof(struct sbar)); // Зменшуємо до 500
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
**Пояснення**: Ця версія безпечно змінює розмір масиву і перевіряє, чи все працює.

### Скріншот
![image](https://github.com/user-attachments/assets/ef9bf90e-8b6d-49b2-a41b-51ac0ee26db6)

## Завдання 4.8: `malloc` у багатопоточному середовищі

### Опис
Дивимося, як `malloc` працює, коли кілька потоків беруть пам’ять.

### Код
```c
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

void *thread_func(void *arg) {
    void *ptr = malloc(100); // Кожен потік бере 100 байтів
    if (ptr == NULL) {
        printf("Потік: Помилка malloc\n");
    } else {
        printf("Потік %ld: Пам’ять виділено: %p\n", (long)arg, ptr);
    }
    sleep(1); // Чекаємо, щоб бачити порядок
    free(ptr);
    return NULL;
}

int main() {
    pthread_t threads[5]; // Створюємо 5 потоків
    for (long i = 0; i < 5; i++) {
        pthread_create(&threads[i], NULL, thread_func, (void *)i);
    }
    for (int i = 0; i < 5; i++) {
        pthread_join(threads[i], NULL); // Чекаємо завершення
    }
    return 0;
}
```
**Пояснення**: Кілька потоків одночасно беруть пам’ять, і система розподіляє її без проблем.

### Скріншот
![image](https://github.com/user-attachments/assets/37543e18-2abf-4fe2-b2e8-94f1df065ea7)

## Висновок
Дізналися, як працюють `malloc`, `realloc` і `reallocarray` у різних випадках, включаючи помилки та багатопоточність.
