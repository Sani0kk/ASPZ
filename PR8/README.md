# Практична робота №8: Робота з файлами та процесами

## Мета роботи
Дослідити поведінку системних викликів для роботи з файлами, сортування даних за допомогою `qsort` і створення процесів через `fork` на FreeBSD.

## Завдання

### Завдання 8.1: Поведінка функції write
#### Опис
Програма перевіряє, чи може системний виклик `write(fd, buffer, nbytes)` повернути значення `count`, відмінне від `nbytes`. Це можливо через обмеження буфера, переривання або помилки (наприклад, нестача місця). Програма створює файл `test.txt` і записує в нього 10 байтів.

#### Код
```c
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>

int main() {
    int fd = open("test.txt", O_WRONLY | O_CREAT | O_TRUNC, 0644);
    if (fd < 0) {
        perror("Помилка відкриття файлу");
        exit(EXIT_FAILURE);
    }

    char buffer[10] = "123456789";
    ssize_t count = write(fd, buffer, 10);
    if (count < 0) {
        perror("Помилка запису");
    } else if (count != 10) {
        printf("Записано %zd байтів замість 10\n", count);
    } else {
        printf("Записано всі 10 байтів\n");
    }

    close(fd);
    return 0;
}
```

#### Скріншот виконання
![image](https://github.com/user-attachments/assets/a1d09c4a-7ebf-482f-88bf-404045735dff)

---

### Завдання 8.2: Читання з файлу після lseek
#### Опис
Програма демонструє роботу `lseek(fd, 3, SEEK_SET)`, який переміщує покажчик на 3-й байт, і `read(fd, &buffer, 4)`, яке зчитує 4 байти. Для послідовності 4, 5, 2, 2, 3, 3, 7, 9, 1, 5 буфер міститиме 2, 2, 3, 3.

#### Код
```c
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>

int main() {
    int fd = open("data.txt", O_WRONLY | O_CREAT | O_TRUNC, 0644);
    if (fd < 0) {
        perror("Помилка відкриття файлу");
        exit(EXIT_FAILURE);
    }
    char data[] = {4, 5, 2, 2, 3, 3, 7, 9, 1, 5};
    write(fd, data, sizeof(data));
    close(fd);

    fd = open("data.txt", O_RDONLY);
    if (fd < 0) {
        perror("Помилка відкриття файлу");
        exit(EXIT_FAILURE);
    }

    lseek(fd, 3, SEEK_SET);
    char buffer[4];
    ssize_t count = read(fd, buffer, 4);
    if (count < 0) {
        perror("Помилка читання");
    } else {
        printf("Буфер: ");
        for (int i = 0; i < count; i++) {
            printf("%d ", buffer[i]);
        }
        printf("\n");
    }

    close(fd);
    return 0;
}
```

#### Скріншот виконання
![image](https://github.com/user-attachments/assets/9649eaf7-3c63-43de-b1fb-47a227aed657)

---

### Завдання 8.3: Аналіз qsort і тести
#### Опис
Програма досліджує найгірші випадки для `qsort` (наприклад, відсортований або зворотньо відсортований масив) і вимірює час виконання. Також включає тест на правильність сортування.

#### Код
```c
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int compare(const void *a, const void *b) {
    return (*(int *)a - *(int *)b);
}

void test_qsort(int *arr, int size, const char *test_name) {
    int *copy = malloc(size * sizeof(int));
    for (int i = 0; i < size; i++) copy[i] = arr[i];
    clock_t start = clock();
    qsort(copy, size, sizeof(int), compare);
    clock_t end = clock();
    double time_spent = (double)(end - start) / CLOCKS_PER_SEC;
    printf("%s: Час виконання %.6f сек\n", test_name, time_spent);
    free(copy);
}

int main() {
    int size = 10000;
    int *arr = malloc(size * sizeof(int));

    // Тест 1: Відсортований масив
    for (int i = 0; i < size; i++) arr[i] = i;
    test_qsort(arr, size, "Відсортований");

    // Тест 2: Зворотньо відсортований масив
    for (int i = 0; i < size; i++) arr[i] = size - i;
    test_qsort(arr, size, "Зворотньо відсортований");

    // Перевірка правильності
    int test_arr[] = {5, 2, 9, 1, 5, 6};
    int expected[] = {1, 2, 5, 5, 6, 9};
    qsort(test_arr, 6, sizeof(int), compare);
    printf("Тест правильності: ");
    int passed = 1;
    for (int i = 0; i < 6; i++) {
        printf("%d ", test_arr[i]);
        if (test_arr[i] != expected[i]) passed = 0;
    }
    printf("(%s)\n", passed ? "Пройдено" : "Не пройдено");

    free(arr);
    return 0;
}
```

#### Скріншот виконання
![image](https://github.com/user-attachments/assets/7136a1de-dbfa-4729-9a84-54b716e509c3)

---

### Завдання 8.4: Завершення програми з fork
#### Опис
Програма створює дочірній процес через `fork` і виводить PID. Батьківський процес повертає PID дочірнього (позитивне число), дочірній — 0, при помилці — -1.

#### Код
```c
#include <stdio.h>
#include <unistd.h>

int main() {
    int pid = fork();
    if (pid < 0) {
        perror("Помилка fork");
        return 1;
    }
    printf("%d\n", pid);
    return 0;
}
```

#### Скріншот виконання
![image](https://github.com/user-attachments/assets/24bba96d-ba35-4526-92b1-3ea29544ff10)

---

### Завдання 8.5: Зміна вмісту файлу без переміщення вказівника
#### Опис
Програма відкриває файл `test.txt`, записує початковий вміст, а потім використовує `pwrite` для зміни перших 3 байтів без переміщення поточного вказівника.

#### Код
```c
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>

int main() {
    int fd = open("test.txt", O_RDWR | O_CREAT | O_TRUNC, 0644);
    if (fd < 0) {
        perror("Помилка відкриття файлу");
        exit(EXIT_FAILURE);
    }

    write(fd, "123456789", 9);
    off_t pos = lseek(fd, 0, SEEK_CUR);
    pwrite(fd, "XXX", 3, 0); // Змінюємо перші 3 байти
    printf("Позиція: %jd, вміст змінено на місці\n", (intmax_t)pos);

    close(fd);
    return 0;
}
```

#### Скріншот виконання
![image](https://github.com/user-attachments/assets/b9e602ff-6689-407f-9066-cb8b4f8e6d0d)
![image](https://github.com/user-attachments/assets/ee7b73cd-90cf-48d7-b47c-3fa091cc0635)

---

## Висновок
Досліджено поведінку системних викликів `write`, `lseek`, `read`, сортування за допомогою `qsort` і створення процесів через `fork` на FreeBSD.
