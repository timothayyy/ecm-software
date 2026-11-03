cmake_minimum_required(VERSION 4.3)
project(ecm C)

set(CMAKE_C_STANDARD 23)

add_executable(ecm main.c
        subfile_1.c
        subfile_1.h)
