#include "Polynomial.hpp"

#include <iostream>
#include <iomanip>
#include <cmath>
#include <algorithm>

namespace {
    // Для сравнения double (чтобы == было адекватным)
    bool almostEqual(double a, double b, double eps = 1e-9) { //Сравнение double через эпсилон
        return std::fabs(a - b) <= eps;  // нужно потому что double часто хранит “почти ноль” типа 1e-15
    }

    // Убираем "хвост" нулей, чтобы степень была корректной
    int trimDegree(int degree, const double* coeff) {
        int d = degree;
        while (d > 0 && almostEqual(coeff[d], 0.0)) {
            --d;
        }
        return d;
    }
}

void Polynomial::allocateAndZero(int degree) {  // Выделяет память для коэффициентов и обнуляет их
    if (degree < 0) degree = 0;
    m_degree = degree;
    m_coeff = new double[m_degree + 1]; //Выделяем динамический массив на m_degree + 1 элементов
    for (int i = 0; i <= m_degree; ++i) {
        m_coeff[i] = 0.0;
    }
}

Polynomial::Polynomial() : m_degree(0), m_coeff(nullptr) {   // по умолчанию: 0  создает полином 0 
    allocateAndZero(0);			// Степень 0, коэффициент 0 => полином 0 (a0 = 0)
}

Polynomial::Polynomial(int degree) : m_degree(0), m_coeff(nullptr) {
    allocateAndZero(degree);			// Степень degree, все коэффициенты 0 => нулевой полином заданной степени
}

Polynomial::Polynomial(int degree, const double* coeffs) : m_degree(0), m_coeff(nullptr) {
    if (degree < 0) degree = 0;
    // сначала копируем, потом подрезаем степень
    allocateAndZero(degree);
    for (int i = 0; i <= degree; ++i) {
        m_coeff[i] = coeffs ? coeffs[i] : 0.0;			//Если coeffs не nullptr  берём coeffs[i] иначе 0.0
    }
    int newDeg = trimDegree(m_degree, m_coeff);		// Убираем "хвост" нулей, чтобы степень была корректной
    if (newDeg != m_degree) {			//Если степень изменилась — надо ужать массив до новой степениw
        // пересоздадим массив ровно под новую степень
        double* old = m_coeff;
        int oldDeg = m_degree;

        allocateAndZero(newDeg);
        for (int i = 0; i <= newDeg; ++i) {
            m_coeff[i] = old[i];
        }

        delete[] old;
        (void)oldDeg;
    }
}

Polynomial::Polynomial(const Polynomial& other) : m_degree(0), m_coeff(nullptr) {   // конструктор копирования
    allocateAndZero(other.m_degree);
    for (int i = 0; i <= m_degree; ++i) {
        m_coeff[i] = other.m_coeff[i];
    }
}

Polynomial& Polynomial::operator=(const Polynomial& other) {
    if (this == &other) {
        return *this;
    }

    double* newArr = new double[other.m_degree + 1];
    for (int i = 0; i <= other.m_degree; ++i) {
        newArr[i] = other.m_coeff[i];
    }

    delete[] m_coeff;
    m_coeff = newArr;
    m_degree = other.m_degree;

    return *this;
}

Polynomial::~Polynomial() {  // деструктор освобождение памяти
    delete[] m_coeff;
    m_coeff = nullptr;
    m_degree = 0;
}

int Polynomial::degree() const {        // возвращает степень полинома
    return m_degree;
}

double Polynomial::coefficient(int power) const { // возвращает коэффициент при x^power, если power вне диапазона -> 0
    if (power < 0 || power > m_degree) return 0.0;
    return m_coeff[power];
}

void Polynomial::setCoefficient(int power, double value) {  // устанавливает коэффициент при x^power, если power > 
    //текущей степени — расширяет полином
    if (power < 0) return;

    if (power <= m_degree) {
        m_coeff[power] = value;

        // если изменили старший коэффициент на 0 — возможно степень уменьшится
        int newDeg = trimDegree(m_degree, m_coeff);// Убираем "хвост" нулей, чтобы степень была корректной
        if (newDeg != m_degree) {
            double* old = m_coeff;
            int oldDeg = m_degree;

            allocateAndZero(newDeg);
            for (int i = 0; i <= newDeg; ++i) {
                m_coeff[i] = old[i];
            }
            delete[] old;
            (void)oldDeg;
        }
        return;
    }

    // power > m_degree: нужно расширить массив
    int newDeg = power;
    double* newArr = new double[newDeg + 1];
    for (int i = 0; i <= newDeg; ++i) newArr[i] = 0.0;

    for (int i = 0; i <= m_degree; ++i) newArr[i] = m_coeff[i];
    newArr[power] = value;

    delete[] m_coeff;
    m_coeff = newArr;
    m_degree = trimDegree(newDeg, m_coeff);
}

double Polynomial::evaluate(double x) const {   // вычисляет значение полинома при данном x
    // Схема Горнера: O(n)
    double result = 0.0;
    for (int i = m_degree; i >= 0; --i) {
        result = result * x + m_coeff[i];
    }
    return result;
}

Polynomial Polynomial::derivative() const { // возвращает производную полинома
    if (m_degree == 0) {
        return Polynomial(); // производная константы = 0
    }

    Polynomial d(m_degree - 1);
    for (int i = 1; i <= m_degree; ++i) {
        d.m_coeff[i - 1] = m_coeff[i] * static_cast<double>(i);
    }

    // подрезать степень (на случай если старшие оказались нулями)
    int newDeg = trimDegree(d.m_degree, d.m_coeff);
    if (newDeg != d.m_degree) {
        Polynomial trimmed(newDeg);
        for (int i = 0; i <= newDeg; ++i) trimmed.m_coeff[i] = d.m_coeff[i];
        return trimmed;
    }

    return d;
}

Polynomial Polynomial::operator+(const Polynomial& rhs) const { // возвращает сумму полиномов
    int maxDeg = std::max(m_degree, rhs.m_degree);// Степень результата не может быть больше максимальной степени слагаемых
    Polynomial res(maxDeg); // создаём полином нужной степени, все коэффициенты изначально 0

    for (int i = 0; i <= maxDeg; ++i) { // складываем коэффициенты при x^i, если i > степени полинома — coefficient(i) вернёт 0
        res.m_coeff[i] = this->coefficient(i) + rhs.coefficient(i);
    }

    int newDeg = trimDegree(res.m_degree, res.m_coeff); // Убираем "хвост" нулей, чтобы степень была корректной 
    if (newDeg != res.m_degree) {   // Если степень изменилась — надо ужать массив до новой степени
        Polynomial trimmed(newDeg); // пересоздадим массив ровно под новую степень
        for (int i = 0; i <= newDeg; ++i) trimmed.m_coeff[i] = res.m_coeff[i]; // скопируем коэффициенты
        return trimmed;
    }

    return res;
}

Polynomial Polynomial::operator-(const Polynomial& rhs) const { // возвращает разность полиномов
    int maxDeg = std::max(m_degree, rhs.m_degree);
    Polynomial res(maxDeg);

    for (int i = 0; i <= maxDeg; ++i) {
        res.m_coeff[i] = this->coefficient(i) - rhs.coefficient(i);
    }

    int newDeg = trimDegree(res.m_degree, res.m_coeff);
    if (newDeg != res.m_degree) {
        Polynomial trimmed(newDeg);
        for (int i = 0; i <= newDeg; ++i) trimmed.m_coeff[i] = res.m_coeff[i];
        return trimmed;
    }

    return res;
}

Polynomial Polynomial::operator*(const Polynomial& rhs) const { // возвращает произведение полиномов
    int deg = m_degree + rhs.m_degree;
    Polynomial res(deg);

    // классическое умножение
    for (int i = 0; i <= m_degree; ++i) {
        for (int j = 0; j <= rhs.m_degree; ++j) {
            res.m_coeff[i + j] += m_coeff[i] * rhs.m_coeff[j];  // коэффициент при x^(i+j) увеличивается на a_i * b_j
        }
    }

    int newDeg = trimDegree(res.m_degree, res.m_coeff); // Убираем "хвост" нулей, чтобы степень была корректной
    if (newDeg != res.m_degree) {
        Polynomial trimmed(newDeg);
        for (int i = 0; i <= newDeg; ++i) trimmed.m_coeff[i] = res.m_coeff[i];
        return trimmed;
    }

    return res;
}

bool Polynomial::operator==(const Polynomial& rhs) const {// сравнивает полиномы на равенство
    int maxDeg = std::max(m_degree, rhs.m_degree);// Если степени разные, это не гарантирует, что полиномы разные (например 0x^2 + 0x + 1 и 1 — оба степени 0), поэтому надо сравнивать коэффициенты
    for (int i = 0; i <= maxDeg; ++i) {
        if (!almostEqual(this->coefficient(i), rhs.coefficient(i))) { // если коэффициенты при x^i отличаются — полиномы не равны
            return false;
        }
    }
    return true;
}

bool Polynomial::operator!=(const Polynomial& rhs) const {  // сравнивает полиномы на неравенство
    return !(*this == rhs);
}

double Polynomial::operator()(double x) const { // позволяет вызвать полином как функцию: p(x) вместо p.evaluate(x) 
    return evaluate(x); 
}

std::ostream& operator<<(std::ostream& os, const Polynomial& p) {
    // Красивый вывод вида: 2x^3 - 5x + 1
    // Если всё ноль -> 0
    bool first = true; // нужен для правильного вывода знаков

    for (int i = p.m_degree; i >= 0; --i) { // идём от старшей степени к младшей, чтобы вывод был в привычном виде
        double a = p.m_coeff[i];    // коэффициент при x^i
        if (almostEqual(a, 0.0)) continue; // пропускаем нулевые коэффициенты

        // знак
        if (!first) {       // не первый член — нужно печатать знак
            os << (a >= 0 ? " + " : " - "); // для положительных печатаем " + ", для отрицательных " - "
        } else {    // первый член — печатаем минус, если он отрицательный
            if (a < 0) os << "-";   // для первого члена просто "-" без пробелов, если он отрицательный
        }

        double absA = std::fabs(a); // абсолютное значение коэффициента, чтобы не печатать двойной минус для отрицательных членов

        // коэффициент (не печатаем 1 перед x, кроме степени 0)
        if (i == 0) {   // свободный член 
            os << absA;
        } else {
            if (!almostEqual(absA, 1.0)) {
                os << absA;
            }
            os << "x";
            if (i != 1) os << "^" << i;
        }

        first = false;
    }

    if (first) {    // если не было ни одного ненулевого коэффициента, значит полином 0
        os << "0";
    }

    return os;
}

std::istream& operator>>(std::istream& is, Polynomial& p) { // Считывает полином из входного потока. Формат ввода:
    // Формат ввода:
    // degree
    // c0 c1 c2 ... c_degree
    int deg;    // степень полинома
    is >> deg;  // Сначала считываем степень, затем коэффициенты от младшего к старшему
    if (!is) return is; 

    if (deg < 0) deg = 0;   // отрицательная степень не имеет смысла, будем считать её 0

    double* tmp = new double[deg + 1];//временный массив для считывания коэффициентов, чтобы не менять объект, если ввод некорректный
    for (int i = 0; i <= deg; ++i) {    // считываем коэффициенты от младшего к старшему
        is >> tmp[i];
        if (!is) {
            delete[] tmp;
            return is;
        }
    }

    // заменяем объект через оператор присваивания
    Polynomial temp(deg, tmp);
    p = temp;

    delete[] tmp;
    return is;
}