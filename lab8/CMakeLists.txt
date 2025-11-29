cmake_minimum_required(VERSION 3.10)

project(lab_students LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(lab_students
    src/main.cpp
    src/student_utils.cpp
)

target_include_directories(lab_students PRIVATE include)
