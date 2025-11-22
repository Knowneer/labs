#include "operations.hpp"
#include <cmath>

namespace lab7 {

//  процессинг оценок через указатель на функцию 
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
}

void filterStudents(StudentArray* arr, bool (*condition)(const Student*)) {     // отметка студентов по условию(которое передаем в main)
    if (!arr || !condition) return;     

    for (int i = 0; i < arr->size; ++i) {
        Student& s = arr->students[i];
        // true/false по условию — пишем в selected
        s.selected = condition(&s);
    }
}

float calculateAverage(const Student* student, float (*weight)(int index)) {        // взвешенное среднее
    if (!student || student->grade_count <= 0 || !weight) return 0.0f;
    float sum = 0.0f;
    float wsum = 0.0f;
    for (int i = 0; i < student->grade_count; ++i) {
        float w = weight(i);          // вес i-й оценки
        sum  += student->grades[i] * w;
        wsum += w;
    }
    if (wsum == 0.0f) return 0.0f;
    return sum / wsum;
}




} 
