cmake_minimum_required(VERSION 3.15)

set(PROJECT_NAME lab7_employee_pointers)
project("${PROJECT_NAME}")

set(CMAKE_CXX_STANDARD 20)

# добавляем исполняемый файл с исходниками
add_executable("${PROJECT_NAME}" main.cpp src/employee.cpp)

# говорим, где лежат наши заголовки (папка include)
target_include_directories("${PROJECT_NAME}" PRIVATE ${CMAKE_SOURCE_DIR}/include)
