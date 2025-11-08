#pragma once
#include <iostream>

namespace lab6 {

struct Employee {
    char* name;   // имя сотрудника (динамическая строка)
    int age;      // возраст
    float salary; // зарплата
};

// Создаёт нового сотрудника в динамической памяти
Employee* create_employee(const char* name, int age, float salary);

// Удаляет сотрудника (освобождает память)
void delete_employee(Employee* emp);

// Увеличивает зарплату (работает через указатель)
void give_salary(Employee* emp, float amount);

// Выводит информацию о сотруднике
void print_employee(const Employee* emp);

// Сравнивает двух сотрудников по возрасту 
void compare_age(const Employee* e1, const Employee* e2, int* result);

} // namespace lab6
