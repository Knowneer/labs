cmake_minimum_required(VERSION 3.16)

project(lab7_employee_pointers LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Собираем исполняемый файл
add_executable(lab7_employee_pointers
    src/main.cpp
    src/data.cpp
    src/operations.cpp
)
