cmake_minimum_required(VERSION 3.10)

project(lab2.1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(lab2.1
    main.cpp
)

target_include_directories(lab2.1 PRIVATE include)
