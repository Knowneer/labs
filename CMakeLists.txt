cmake_minimum_required(VERSION 3.15)

set(PROJECT_NAME lab7_students_grades)
project("${PROJECT_NAME}")

set(CMAKE_CXX_STANDARD 20)

add_executable("${PROJECT_NAME}"
    main.cpp          # main лежит в корне
    src/data.cpp
    src/operations.cpp
)

# ВАЖНО: добавить путь к заголовкам
target_include_directories("${PROJECT_NAME}" PRIVATE include)
