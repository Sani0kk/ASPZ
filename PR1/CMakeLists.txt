cmake_minimum_required(VERSION 3.5)
project(MyProgram C)

set(CMAKE_C_FLAGS "-Wall -O2 -g")

include_directories(${CMAKE_SOURCE_DIR})

link_directories(/usr/lib /home/sani0kk/mylibs)

add_executable(my_program main.c input.c output.c)
target_link_libraries(my_program process1 process)