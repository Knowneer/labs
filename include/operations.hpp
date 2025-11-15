#pragma once
#include "data.hpp"
#include <functional> // для перегрузки с std::function

namespace lab7 {


// Применить операцию ко всем оценкам всех студентов (указатель на функцию)
void processGrades(lab7::StudentArray* arr, float (*operation)(float));

// Перегрузка под лямбды с захватом (std::function) — чтобы можно было нормализовать по max
void processGrades(lab7::StudentArray* arr, const std::function<float(float)>& operation);



} // namespace lab7
