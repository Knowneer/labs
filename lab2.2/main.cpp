#include "Polynomial.hpp"
#include <iostream>


/*
1.
class Array {
private:
    int* data;
    int size;

public:
    Array(int n) {
        size = n;
        data = new int[size];
    }

    ~Array() {                 // 1. Деструктор
        delete[] data;
    }

    Array(const Array& other) {   // 2. Конструктор копирования
        size = other.size;
        data = new int[size];
        for (int i = 0; i < size; i++)
            data[i] = other.data[i];
    }

    Array& operator=(const Array& other) {   // 3. Оператор присваивания
        if (this == &other)
            return *this;

        delete[] data;

        size = other.size;
        data = new int[size];
        for (int i = 0; i < size; i++)
            data[i] = other.data[i];

        return *this;
    }

Если их не написать:
компилятор создаст их сам
будет поверхностное копирование  копируется только адрес массива
два объекта будут указывать на один и тот же массив
при удалении произойдёт двойное освобождение памяти

2.
std::ostream& operator<<(std::ostream& out, const Array& obj);

возвращаем std::ostream& — чтобы можно было писать цепочкой:
std::cout << obj << std::endl;


3.
Константными (const) должны быть методы, которые не изменяют объект
int getSize() const {
    return size;
}
Если метод не меняет поля класса — он обязан быть const
Иначе нельзя будет вызвать его у константного объекта
const Array a(5);
a.getSize();   // сработает только если метод const

4.
this — это неявный указатель на текущий объект класса

неявное использование 
size = other.size;
this->size = other.size;

5.
.h
#ifndef ARRAY_H
#define ARRAY_H

class Array {
    ...
};

#endif

.cpp
#include "Array.h"

main.cpp
#include "Array.h"

};

*/

int main() {
    // 1) Создание объектов разными способами
    Polynomial p0;                 // default
    Polynomial p1(3);              // степень 3, все коэффициенты 0

    // p2(x) = 1 - 5x + 2x^3
    double c2[] = {1.0, -5.0, 0.0, 2.0};
    Polynomial p2(3, c2);

    std::cout << "p0 = " << p0 << "\n";
    std::cout << "p1 = " << p1 << "\n";
    std::cout << "p2 = " << p2 << "\n\n";

    // setCoefficient
    p1.setCoefficient(0, 7.0);
    p1.setCoefficient(1, 3.0);
    p1.setCoefficient(2, -1.0); // p1(x)=7+3x-x^2
    std::cout << "After setCoefficient:\n";
    std::cout << "p1 = " << p1 << "\n\n";

    // 2) Копирование объектов (copy ctor)
    Polynomial copyP2(p2);
    std::cout << "copyP2 (copy of p2) = " << copyP2 << "\n";

    // 3) Присваивание объектов
    Polynomial assigned;
    assigned = p1;
    std::cout << "assigned (after assigned = p1) = " << assigned << "\n\n";

    // 4) Работа перегруженных операторов + - *
    Polynomial sum = p1 + p2;
    Polynomial diff = p1 - p2;
    Polynomial prod = p1 * p2;

    std::cout << "p1 + p2 = " << sum << "\n";
    std::cout << "p1 - p2 = " << diff << "\n";
    std::cout << "p1 * p2 = " << prod << "\n\n";

    // 5) Сравнение == !=
    std::cout << "p2 == copyP2 ? " << (p2 == copyP2 ? "true" : "false") << "\n";
    std::cout << "p2 != copyP2 ? " << (p2 != copyP2 ? "true" : "false") << "\n\n";

    // 6) Оператор вызова функции () и evaluate
    double x = 2.0;
    std::cout << "p1(" << x << ") = " << p1(x) << "\n";
    std::cout << "p2.evaluate(" << x << ") = " << p2.evaluate(x) << "\n\n";

    // 7) Производнаяw
    Polynomial dp1 = p1.derivative();
    Polynomial dp2 = p2.derivative();
    std::cout << "p1' = " << dp1 << "\n";
    std::cout << "p2' = " << dp2 << "\n\n";

    // 8) Использование константных объектов
    const Polynomial constP = p2;
    std::cout << "constP = " << constP << "\n";
    std::cout << "constP.degree() = " << constP.degree() << "\n";
    std::cout << "constP(3) = " << constP(3.0) << "\n\n";

    // 9) Демонстрация ввода >>
    // Ввод формата:
    // deg
    // c0 c1 ... c_deg
    // Пример:
    // 2
    // 1 0 -4
    // -> 1 - 4x^2
    std::cout << "Enter polynomial in format:\n";
    std::cout << "degree then coefficients c0..c_degree\n";
    std::cout << "Example:\n2\n1 0 -4\n\n";

    Polynomial userP;
    if (std::cin >> userP) {
        std::cout << "You entered: " << userP << "\n";
        std::cout << "Derivative: " << userP.derivative() << "\n";
    } else {
        std::cout << "Input error.\n";
    }   

    return 0;
}