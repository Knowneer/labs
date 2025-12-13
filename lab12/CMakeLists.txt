cmake_minimum_required(VERSION 3.10)

project(lab_10 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(lab_11
    src/main.cpp
    src/dictionary.cpp
)

target_include_directories(lab_11 PRIVATE include)
