cmake_minimum_required(VERSION 4.3)
project(ecm C)

set(CMAKE_C_STANDARD 23)

add_executable(ecm
        main.c
        src/subfile_1.c
)

target_include_directories(ecm PRIVATE include)
