#include "operations.hpp"
#include <cmath>

namespace lab7 {

// === Иса: процессинг оценок через указатель на функцию ===
void processGrades(StudentArray* arr, float (*operation)(float)) {
    if (!arr || !operation) return;
    for (int i = 0; i < arr->size; ++i) {
        Student& s = arr->students[i];
        for (int j = 0; j < s.grade_count; ++j) {
            s.grades[j] = operation(s.grades[j]); // по значению -> вернуть новое значение
        }
    }
}

// Перегрузка под std::function — позволяет использовать лямбды с захватом
void processGrades(StudentArray* arr, const std::function<float(float)>& operation) {		
    if (!arr || !operation) return;
    for (int i = 0; i < arr->size; ++i) {
        Student& s = arr->students[i];
        for (int j = 0; j < s.grade_count; ++j) {
            s.grades[j] = operation(s.grades[j]);
        }
    }
}} 