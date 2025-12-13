cmake_minimum_required(VERSION 3.10)

project(lab_10 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(lab_10
    src/main.cpp
    src/caesar.cpp
)

target_include_directories(lab_10 PRIVATE include)
