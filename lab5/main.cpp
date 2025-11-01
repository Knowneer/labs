#include <iostream>
#include <string>
#include "calculator.hpp"

static void usage() {
    std::cout << "Введите: <число> <основание>\n"
                 "Основания: 2, 8, 10, 16\n"
                 "Примеры:\n"
                 "  42 10\n"
                 "  101010 2\n"
                 "  FF 16\n"
                 "  77 8\n";
}

int main() {
    std::string token;
    int base = 0;

    if (!(std::cin >> token >> base)) {
        std::cout << "Ошибка ввода.\n";
        usage();
        return 1;
    }

    if (!basecalc::is_supported_base(base)) {
        std::cout << "Ошибка: поддерживаются только 2, 8, 10, 16.\n";
        return 1;
    }

    // Превратим ввод в C-строку, подчистим и проверим
    char cleaned[128];
    if (!basecalc::clean_input(token.c_str(), cleaned, sizeof(cleaned))) {
        std::cout << "Ошибка: строка слишком длинная или пустая.\n";
        return 1;
    }

    if (base == basecalc::BASE_DEC) {
        long long val = 0;
        if (!basecalc::from_base_string(cleaned, basecalc::BASE_DEC, &val)) {
            std::cout << "Ошибка: некорректное десятичное число или переполнение.\n";
            return 1;
        }
        char b2[70], b8[70], b16[70];
        if (!basecalc::to_base_string(val, basecalc::BASE_BIN, b2, sizeof(b2)) ||
            !basecalc::to_base_string(val, basecalc::BASE_OCT, b8, sizeof(b8)) ||
            !basecalc::to_base_string(val, basecalc::BASE_HEX, b16, sizeof(b16))) {
            std::cout << "Ошибка: буфер мал при выводе.\n";
            return 1;
        }
        std::cout << "Вход (10): " << cleaned << "\n";
        std::cout << "База 2 : " << b2  << "\n";
        std::cout << "База 8 : " << b8  << "\n";
        std::cout << "База 16: " << b16 << "\n";
    } else {
        long long val = 0;
        if (!basecalc::from_base_string(cleaned, base, &val)) {
            std::cout << "Ошибка: некорректные символы/переполнение для основания " << base << ".\n";
            return 1;
        }
        std::cout << "Вход (" << base << "): " << cleaned << "\n";
        std::cout << "Десятичная (10): " << val << "\n";
    }

    return 0;
}
