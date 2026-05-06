cmake_minimum_required(VERSION 3.16)
project(clox_chapter23_base C)

set(CMAKE_C_STANDARD 99)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_C_EXTENSIONS OFF)

add_executable(clox
  chunk.c
  compiler.c
  debug.c
  main.c
  memory.c
  object.c
  scanner.c
  table.c
  value.c
  vm.c
)

if (MSVC)
  target_compile_options(clox PRIVATE /W4)
else()
  target_compile_options(clox PRIVATE -Wall -Wextra -Wpedantic)
endif()
