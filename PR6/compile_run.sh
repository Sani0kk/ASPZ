#!/bin/sh
  # Компіляція з прапором -g для налагодження
  gcc -Wall -g -o test_program test_program.c
  # Запуск valgrind з опціями для перевірки витоків
  valgrind --leak-check=full --track-origins=yes ./test_program
