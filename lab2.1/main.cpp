#include <iostream>

/*
Вариант 5
1.Преимущества ООП

Инкапсуляция данных
Данные защищены от прямого доступа, с ними можно работать только через методы

Лучшая структура программы
Код разбит на классы и объекты, каждый из которых отвечает за свою задачу

Масштабируемость
ООП удобнее для больших проектов — проще добавлять новый функционал


Недостатки ООП

Сложнее для новичков
Нужно понимать классы, конструкторы, области видимости

Избыточность для маленьких программ
Для простых задач процедурный код может быть быстрее и проще.

2.
Инкапсуляция — это сокрытие внутреннего состояния объекта и предоставление доступа к нему только через публичные методы

private — для данных
public — для методов

3.
Конструктор по умолчанию
Rectangle();
не принимает параметров
создаёт объект с начальными значениями


Параметризованный конструктор
Rectangle(double length, double width);
принимает параметры
позволяет сразу задать состояние объекта



4.Member initializer list — это:
Rectangle(double l, double w)
    : length(l), width(w) {} 


Обязательно использовать, если:
Поля const
const int x;
Поля-ссылки
int& ref;		


5.
Оператор разыменования *
Используется для получения объекта, на который указывает указатель

Rectangle* ptr = new Rectangle(5, 3);
Rectangle r = *ptr;

Оператор стрелка ->
Используется для доступа к членам объекта через указатель.
ptr->getArea();


Связь между * и ->
ptr->getArea();
эквивалентно:
(*ptr).getArea();

*/

class Rectangle { 
private:
    double length;
    double width;

public:
    // Конструктор по умолчанию
    Rectangle() : length(0.0), width(0.0) {
        std::cout << "Вызван конструктор по умолчанию\n";
    }

    // Параметризованный конструктор (через member initializer list)
    Rectangle(double length, double width)
        : length(length), width(width) {
        std::cout << "Вызван параметризованный конструктор\n";
    }

    // Деструктор
    ~Rectangle() {
        std::cout << "Объект Rectangle удалён\n";
    }

    // Геттеры
    double getLength() const {
        return length;
    }

    double getWidth() const {
        return width;
    }

    // Сеттеры
    void setLength(double length) {
        this->length = length;
    }

    void setWidth(double width) {
        this->width = width;
    }

    // Метод изменения размеров
    void resize(double newLength, double newWidth) {
        length = newLength;
        width = newWidth;
    }

    // Вычисление площади
    double getArea() const {
        return length * width;
    }

    // Вычисление периметра
    double getPerimeter() const {
        return 2 * (length + width);
    }

    // Проверка: является ли квадратом
    bool isSquare() const {
        return length == width;
    }

    // Вывод информации об объекте
    void printInfo() const {
        std::cout << "Прямоугольник:\n";
        std::cout << "Длина = " << length << "\n";
        std::cout << "Ширина = " << width << "\n";
        std::cout << "Площадь = " << getArea() << "\n";
        std::cout << "Периметр = " << getPerimeter() << "\n";
        std::cout << "Квадрат? " << (isSquare() ? "Да" : "Нет") << "\n";
    }
};

int main() {
    // Создание объекта конструктором по умолчанию
    Rectangle r1;
    r1.setLength(5);
    r1.setWidth(3);
    r1.printInfo();

    std::cout << "\n";

    // Создание объекта параметризованным конструктором
    Rectangle r2(4, 4);
    r2.printInfo();

    std::cout << "\n";

    // Работа с указателем на объект
    Rectangle* ptr = new Rectangle(10, 2);
    ptr->printInfo();

    // Изменение размеров через указатель
    ptr->resize(6, 6);
    std::cout << "\nПосле изменения размеров:\n";
    ptr->printInfo();

    // Освобождение памяти (вызов деструктора)
    delete ptr;

    return 0;
}
