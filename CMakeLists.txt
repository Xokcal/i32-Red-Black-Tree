cmake_minimum_required(VERSION 3.27)
project(i32_Black_Red C)

set(CMAKE_C_STANDARD 11)

add_executable(i32_Black_Red BlackRed/main.c
        BlackRed/blackRedTree.c
        BlackRed/blackRedTree.h
        BlackRed/typedef.h
)
