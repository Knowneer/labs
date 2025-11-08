#include "employee.hpp"
#include <cstring> // strlen, strcpy
#include <iostream>

namespace lab6
{

    Employee *create_employee(const char *name, int age, float salary)
    {
        if (!name || age <= 0 || salary < 0.0f)
        {
            std::cerr << "Некорректные данные при создании сотрудника\n";
            return nullptr;
        }

        // Выделяем память под структуру
        Employee *emp = new Employee;

        // Выделяем память под имя
        emp->name = new char[strlen(name) + 1];
        std::strcpy(emp->name, name);

        emp->age = age;
        emp->salary = salary;
        return emp;
    }

    void delete_employee(Employee *emp)
    {
        if (!emp)
            return;

        delete[] emp->name; // освобождаем память строки
        emp->name = nullptr;

        delete emp; // освобождаем сам объект
    }

    void give_salary(Employee *emp, float amount)
    {
        if (!emp || amount <= 0)
            return;
        emp->salary += amount;
    }

    void print_employee(const Employee *emp)
    {
        if (!emp)
            return;
        std::cout << "Имя: " << emp->name
                  << ", Возраст: " << emp->age
                  << ", Зарплата: " << emp->salary << "\n";
    }

    void compare_age(const Employee *e1, const Employee *e2, int *result)
    {
        if (!e1 || !e2 || !result)
            return;
        if (e1->age > e2->age)
            *result = 1; // e1 старше e2
        else if (e1->age < e2->age)
            *result = -1; // e1 младше e2
        else
            *result = 0; // ровесники
    }

} // namespace lab6
