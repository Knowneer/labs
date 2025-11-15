#include <iostream>
#include <cmath>
#include "data.hpp"
#include "operations.hpp"

using namespace lab7;

// === Примеры операций, которые подходят как "указатель на функцию" ===
static float round_op(float x) { return std::round(x); }
static float clamp_0_100(float x) {
    if (x < 0.f) x = 0.f;
    if (x > 100.f) x = 100.f;
    return x;
}

// === Условие для filterStudents: «отличник», если средняя >= 90 (без весов) ===
static bool is_excellent(const Student* s) {
    if (!s || s->grade_count <= 0) return false;
    float sum = 0.f;
    for (int i = 0; i < s->grade_count; ++i) sum += s->grades[i];
    float avg = sum / s->grade_count;
    return avg >= 90.f;
}

// === Веса: равномерные (пример указателя на функцию) ===
static float weight_equal(int /*index*/) { return 1.0f; }

int main() {
    // 1) создаём массив из 3 студентов (динамически)
    StudentArray* arr = createStudentArray(3);

    // 2) заполняем руками (как пример; на защите можете читать из ввода)
    // Студент 0
    arr->students[0].name = dup_cstr("Иван");
    alloc_grades(arr->students[0], 4);
    arr->students[0].grades[0] = 78;
    arr->students[0].grades[1] = 82.5f;
    arr->students[0].grades[2] = 90;
    arr->students[0].grades[3] = 74;

    // Студент 1
    arr->students[1].name = dup_cstr("Мария");
    alloc_grades(arr->students[1], 3);
    arr->students[1].grades[0] = 99.5f;
    arr->students[1].grades[1] = 100.0f;
    arr->students[1].grades[2] = 89.0f;

    // Студент 2
    arr->students[2].name = dup_cstr("Антон");
    alloc_grades(arr->students[2], 5);
    arr->students[2].grades[0] = 30;
    arr->students[2].grades[1] = 55;
    arr->students[2].grades[2] = 60;
    arr->students[2].grades[3] = 72;
    arr->students[2].grades[4] = 81;

    std::cout << "Исходные данные:\n";
    print_students(arr);

    // === Иса: применяем processGrades с указателем на функцию ===
    processGrades(arr, clamp_0_100);  // ограничим в 0..100
    processGrades(arr, round_op);     // округлим

    std::cout << "\nПосле clamp + round:\n";
    print_students(arr);

    // === Лямбда с захватом: нормализация на максимум (0..100)
    float mx = max_grade(arr);                       // находим максимум
    if (mx > 0.f) {
        auto normalize = [mx](float x) -> float {    // ЛЯМБДА С ЗАХВАТОМ!
            return (x / mx) * 100.0f;
        };
        processGrades(arr, normalize);               // перегрузка со std::function
    }
    std::cout << "\nПосле нормализации на максимум:\n";
    print_students(arr);
