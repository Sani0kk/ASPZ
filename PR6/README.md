# Практична робота №6: Використання `valgrind`

## Мета роботи
Навчитися перевіряти програму на витоки пам’яті за допомогою скрипта та `valgrind`.

## Завдання 6.1: Скрипт для компіляції та запуску з `valgrind`

### Опис
Створюємо скрипт, який компілює код і перевіряє витоки пам’яті.

### Код
```sh
#!/bin/sh
# Компіляція з прапором -g для налагодження
gcc -Wall -g -o test_program test_program.c
# Запуск valgrind з опціями для перевірки витоків
valgrind --leak-check=full --track-origins=yes ./test_program
```
**Пояснення**: Скрипт спочатку робить програму з інформацією для перевірки, а потім запускає `valgrind`, щоб знайти, чи не забули звільнити пам’ять.

### Код для тестування (test_program.c)
```c
#include <stdlib.h>
#include <stdio.h>

int main() {
    int *ptr = malloc(10 * sizeof(int)); // Беремо пам’ять
    if (ptr == NULL) {
        printf("Помилка виділення\n");
        return 1;
    }
    printf("Пам’ять виділено: %p\n", (void *)ptr);
    // Не звільняємо пам’ять — витік!
    return 0;
}
```
**Пояснення**: Ця програма бере пам’ять, але не повертає її назад, що і перевіряємо.

### Компіляція та виконання
```sh
chmod +x compile_run.sh
./compile_run.sh
```

### Виконання
```sh
./compile_run.sh
```

### Скріншот
![image](https://github.com/user-attachments/assets/9548e1b4-a9e4-4723-8b61-87ee375b56e2)
![image](https://github.com/user-attachments/assets/3ea1e071-620a-4433-9614-c0ef78aee605)

## Висновок
Дізналися, як скрипт із `valgrind` допомагає знаходити витоки пам’яті.
