#include "data.hpp"
#include <cstring>
#include <iostream>

namespace lab7 {

StudentArray* createStudentArray(int size) {
    if (size <= 0) return nullptr; 
    StudentArray* arr = new StudentArray;  
    arr->size = size; 
    arr->students = new Student[size];  
    for (int i = 0; i < size; ++i) {   
        arr->students[i].name = nullptr;	 
        arr->students[i].grades = nullptr;
        arr->students[i].grade_count = 0;
        arr->students[i].selected = false;
    }
    return arr;
}

void deleteStudentArray(StudentArray* arr) {	
    if (!arr) return;		
    for (int i = 0; i < arr->size; ++i) {		
        Student& s = arr->students[i];
        delete[] s.name;   s.name = nullptr;
        delete[] s.grades; s.grades = nullptr;
        s.grade_count = 0;
    }
    delete[] arr->students;
    arr->students = nullptr;
    arr->size = 0;
    delete arr;
}

char* dup_cstr(const char* src) {		
    if (!src) return nullptr;
    std::size_t n = std::strlen(src);		
    char* p = new char[n + 1];	
    std::memcpy(p, src, n + 1);	
    return p;
}

bool alloc_grades(Student& st, int grade_count) {		
    if (grade_count <= 0) return false;		
    st.grades = new float[grade_count];
    st.grade_count = grade_count;
    for (int i = 0; i < grade_count; ++i) st.grades[i] = 0.0f;
    return true;
}

float max_grade(const StudentArray* arr) {
    if (!arr || arr->size <= 0) return 0.0f;
    float mx = 0.0f;
    for (int i = 0; i < arr->size; ++i) {
        const Student& s = arr->students[i];
        for (int j = 0; j < s.grade_count; ++j) {
            if (s.grades[j] > mx) mx = s.grades[j];
        }
    }
    return mx;
}

void print_students(const StudentArray* arr) {
    if (!arr) return;
    for (int i = 0; i < arr->size; ++i) {
        const Student& s = arr->students[i];
        std::cout << (s.name ? s.name : "(null)") << "  [";
        for (int j = 0; j < s.grade_count; ++j) {
            std::cout << s.grades[j];
            if (j + 1 < s.grade_count) std::cout << ", ";
        }
        std::cout << "]  selected=" << (s.selected ? "true" : "false") << "\n";
    }
}

} // namespace lab7
