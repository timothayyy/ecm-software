cmake_minimum_required(VERSION 4.3)
project(ecm C)

set(CMAKE_C_STANDARD 23)

add_executable(ecm
        main.c
        include/subfile_1.h
        src/subfile_1.c
        include/ecm_RAM.h
        src/ecm_RAM.c
        include/canbus.h
)

target_include_directories(ecm PRIVATE include)
