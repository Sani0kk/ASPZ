# Практична робота №1: Компіляція багатофайлової програми та створення бібліотек

## Мета роботи
Оволодіти навичками компіляції багатофайлових програм на C за допомогою `gcc`, створенням статичних і динамічних бібліотек, а також автоматизацією збирання через `Makefile` і `CMake`.

## Завдання 1: Компіляція багатофайлової програми

### Опис
Програма складається з файлів `main.c`, `input.c`, `output.c` та використовує бібліотеки `libprocess1` (`/usr/lib`) і `libprocess` (`~/mylibs`). `main.c` викликає функції для введення числа, його обробки та виведення результатів.

### Код файлів

#### main.c
```c
#include <stdio.h>
#include "input.h"
#include "output.h"
#include "process1.h"
#include "process.h"

int main() {
    int value = get_input();
    int processed1 = process1(value);
    int processed2 = process(value);
    print_output(processed1, processed2);
    return 0;
}
```

#### input.c
```c
#include <stdio.h>
#include "input.h"

int get_input() {
    int value;
    printf("Введіть число: ");
    scanf("%d", &value);
    return value;
}
```

#### output.c
```c
#include <stdio.h>
#include "output.h"

void print_output(int result1, int result2) {
    printf("Результат process1: %d\n", result1);
    printf("Результат process: %d\n", result2);
}
```

### Команди компіляції

#### Базова компіляція
```sh
gcc -c input.c output.c
gcc main.c input.o output.o -L/usr/lib -lprocess1 -L~/mylibs -lprocess -o my_program
```

#### Використання `libprocess1` із `/usr/lib`
```sh
gcc main.c input.o output.o -L/usr/lib -lprocess1 -o my_program
```

#### Використання `libprocess` із `~/mylibs`
```sh
gcc main.c input.o output.o -L~/mylibs -lprocess -o my_program
```

#### З прапорами `-g` і `-O2`
```sh
gcc -g -O2 main.c input.o output.o -L/usr/lib -lprocess1 -L~/mylibs -lprocess -o my_program
```

### Скріншот компіляції
![Скріншот компіляції](compilation_screenshot.png)

---

## Завдання 2: Створення статичних і динамічних бібліотек

### Опис
Створюємо статичні (`libprocess1.a`, `libprocess.a`) та динамічні (`libprocess1.so`, `libprocess.so`) бібліотеки з файлів `process1.c` і `process.c`.

### Код бібліотек

#### process1.c
```c
#include "process1.h"

int process1(int value) {
    return value * 2;
}
```

#### process.c
```c
#include "process.h"

int process(int value) {
    return value + 10;
}
```

### Створення бібліотек

#### Статичні бібліотеки
```sh
gcc -c process1.c -o process1.o
gcc -c process.c -o process.o
ar rcs libprocess1.a process1.o
ar rcs libprocess.a process.o
mv libprocess1.a /usr/lib/
mv libprocess.a ~/mylibs/
```

#### Динамічні бібліотеки
```sh
gcc -c -fPIC process1.c -o process1.o
gcc -shared -o libprocess1.so process1.o
gcc -c -fPIC process.c -o process.o
gcc -shared -o libprocess.so process.o
mv libprocess1.so /usr/lib/
mv libprocess.so ~/mylibs/
```

#### Компіляція з бібліотеками
- Статична:
```sh
gcc main.c input.o output.o -L/usr/lib -lprocess1 -L~/mylibs -lprocess -o my_program_static
```
- Динамічна:
```sh
gcc main.c input.o output.o -L/usr/lib -lprocess1 -L~/mylibs -lprocess -o my_program_dynamic
export LD_LIBRARY_PATH=$LD_LIBRARY_PATH:/usr/lib:~/mylibs
```

### Порівняння виконання
| Тип бібліотеки | Команда запуску          | Особливості                              |
|----------------|--------------------------|------------------------------------------|
| Статична       | ./my_program_static      | Більший розмір файлу, незалежний від бібліотек |
| Динамічна      | ./my_program_dynamic     | Менший розмір, потребує бібліотеки під час виконання |

### Скріншот виконання
![Скріншот виконання](execution_screenshot.png)

### Скріншот аналізу сегментів
![Скріншот аналізу сегментів](size_screenshot.png)

---

## Завдання 3: Makefile

### Код Makefile
```make
CC = gcc
CFLAGS = -g -O2
LDFLAGS = -L/usr/lib -lprocess1 -L~/mylibs -lprocess
OBJ = main.o input.o output.o
TARGET = my_program

all: $(TARGET)

$(TARGET): $(OBJ)
	$(CC) $(OBJ) $(LDFLAGS) -o $(TARGET)

main.o: main.c input.h output.h process1.h process.h
	$(CC) $(CFLAGS) -c main.c

input.o: input.c input.h
	$(CC) $(CFLAGS) -c input.c

output.o: output.c output.h
	$(CC) $(CFLAGS) -c output.c

clean:
	rm -f *.o $(TARGET)

.PHONY: all clean
```

### Використання
```sh
make
make clean
```

---

## Завдання 4: CMakeLists.txt

### Код CMakeLists.txt
```cmake
cmake_minimum_required(VERSION 3.10)
project(MyProgram C)

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -g -O2")

add_executable(my_program main.c input.c output.c)

target_link_directories(my_program PRIVATE /usr/lib ${CMAKE_SOURCE_DIR}/mylibs)
target_link_libraries(my_program PRIVATE process1 process)
```

### Використання
```sh
mkdir build
cd build
cmake ..
make
```

### Скріншот збирання через CMake
![Скріншот CMake](cmake_screenshot.png)

## Висновок
- Опановано компіляцію багатофайлових програм із різними бібліотеками.
- Створено статичні та динамічні бібліотеки, досліджено їх вплив на розмір і виконання програми.
- Автоматизовано збирання за допомогою `Makefile` і `CMake`.
