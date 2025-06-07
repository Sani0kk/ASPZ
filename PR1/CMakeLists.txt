cmake_minimum_required(VERSION 3.10)
project(MyProgram C)

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -g -O2")

add_executable(my_program main.c input.c output.c)

target_link_directories(my_program PRIVATE /usr/lib ${CMAKE_SOURCE_DIR}/mylibs)
target_link_libraries(my_program PRIVATE process1 process)
