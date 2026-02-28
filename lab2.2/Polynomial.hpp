#ifndef POLYNOMIAL_H
#define POLYNOMIAL_H

#include <iosfwd>   // forward declarations for iostream
#include <cstddef>  // std::size_t

class Polynomial {
private:
    int m_degree;       // степень полинома (>= 0)
    double* m_coeff;    // динамический массив коэффициентов размера (m_degree + 1)
                        // m_coeff[i] — коэффициент при x^i

    void allocateAndZero(int degree);

public:
    // --- Rule of 3 ---
    Polynomial();                         // по умолчанию: 0
    explicit Polynomial(int degree);      // нулевой полином заданной степени
    Polynomial(int degree, const double* coeffs); // копирует coeffs[0..degree]
    Polynomial(const Polynomial& other);  // deep copy
    Polynomial& operator=(const Polynomial& other); // self-check + deep copy
    ~Polynomial();                        // освобождение памяти

    // --- Константные методы ---
    int degree() const;
    double coefficient(int power) const;  // безопасно: если power вне диапазона -> 0

    // --- Методы работы с данными ---
    void setCoefficient(int power, double value);
    double evaluate(double x) const;
    Polynomial derivative() const;

    // --- Операторы ---
    Polynomial operator+(const Polynomial& rhs) const;
    Polynomial operator-(const Polynomial& rhs) const;
    Polynomial operator*(const Polynomial& rhs) const;

    bool operator==(const Polynomial& rhs) const;
    bool operator!=(const Polynomial& rhs) const;

    double operator()(double x) const; // вызов как функции

    // --- Ввод/вывод ---
    friend std::ostream& operator<<(std::ostream& os, const Polynomial& p);
    friend std::istream& operator>>(std::istream& is, Polynomial& p);
};

#endif // POLYNOMIAL_H