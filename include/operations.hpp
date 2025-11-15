#pragma once
#include "data.hpp"
#include <functional> // для перегрузки с std::function

namespace lab7 {


// Применить операцию ко всем оценкам всех студентов (указатель на функцию)
void processGrades(lab7::StudentArray* arr, float (*operation)(float));

// Перегрузка под лямбды с захватом (std::function) — чтобы можно было нормализовать по max
void processGrades(lab7::StudentArray* arr, const std::function<float(float)>& operation);



// Отметить студентов по условию (condition возвращает true/false)
void filterStudents(lab7::StudentArray* arr, bool (*condition)(const lab7::Student*));

// Взвешенное среднее одной записи (указатель на функцию веса)
float calculateAverage(const lab7::Student* student, float (*weight)(int index));

} // namespace lab7
