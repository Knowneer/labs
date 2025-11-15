cmake_minimum_required(VERSION 3.15)

set(PROJECT_NAME lab7_students_grades)
project("${PROJECT_NAME}")

set(CMAKE_CXX_STANDARD 20)

add_executable("${PROJECT_NAME}"
    src/main.cpp
    src/data.cpp
    src/operations.cpp
)