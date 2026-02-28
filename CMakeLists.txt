cmake_minimum_required(VERSION 3.10)

project(lab2.2 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(lab2.2
    main.cpp
    Polynomial.cpp
)

target_include_directories(lab2.2 PRIVATE include)
