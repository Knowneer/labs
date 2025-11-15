#pragma once
#include <cstddef> 

namespace lab7 {

struct Student {
    char* name;        
    float* grades;     
    int    grade_count;
    bool   selected;  
};

struct StudentArray {
    Student* students; 
    int size;
};



// Выделить массив студентов (без имён и оценок внутри)
StudentArray* createStudentArray(int size);

// Полностью удалить массив студентов (освобождает всё внутри)
void deleteStudentArray(StudentArray* arr);

// Создать/скопировать строку name в динамической памяти (возвращает char*)	
char* dup_cstr(const char* src);

// Создать оценки студента (выделяет grades на grade_count, заполняет нулями)
bool alloc_grades(Student& st, int grade_count);

// Найти максимальную оценку среди всех (для нормализации). Если нет оценок — вернуть 0.0f
float max_grade(const StudentArray* arr);

// Напечатать массив студентов (имя, оценки, selected)
void print_students(const StudentArray* arr);

} // namespace lab7
