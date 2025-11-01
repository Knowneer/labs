#include "calculator.hpp"

#include <cctype>  
#include <climits>  
#include <cstring>  

namespace basecalc {

    // Проверяет, поддерживается ли основание
bool is_supported_base(int base) noexcept {
    return base == BASE_BIN || base == BASE_OCT || base == BASE_DEC || base == BASE_HEX;
}

    // Вспомогательная функция для проверки, является ли символ буквой A..F или a..f
static bool is_hex_letter(char c) noexcept {
    return (c >= 'a' && c <= 'f') || (c >= 'A' && c <= 'F');
}


    // static = "внутренняя", видна только внутри этого файла calculator.cpp (чтобы не мешала в других файлах).
    //noexcept = функция обещает не выбрасывать исключений.(ошибок)  


// Очищает строку ввода: убирает пробелы в начале и конце, 
// делает буквы a..f заглавными (A..F), чтобы унифицировать HEX.
// Записывает результат в out_buf, если хватает места.
bool clean_input(const char* in, char* out, std::size_t out_sz) noexcept {
    // Проверяем, что указатели не нулевые и буфер не нулевой длины
    if (!in || !out || out_sz == 0) return false;

    //  Находим начало без пробелов
    const char* start = in;
    while (*start && std::isspace(static_cast<unsigned char>(*start))) ++start;

    // Находим конец строки
    const char* end = start;
    while (*end) ++end;

    //  Отступаем назад, пока справа пробелы
    while (end > start && std::isspace(static_cast<unsigned char>(*(end - 1)))) --end;

    //  Считаем длину чистой строки
    std::size_t need = static_cast<std::size_t>(end - start);
    if (need + 1 > out_sz) return false; // +1 для '\0' (терминатор строки)

    //  Копируем символы в новый буфер, заменяя a..f → A..F
    for (std::size_t i = 0; i < need; ++i) {
        char c = start[i];
        if (c >= 'a' && c <= 'f') {
            c = static_cast<char>(std::toupper(static_cast<unsigned char>(c)));
        }
        out[i] = c;
    }

    //  Добавляем нуль-терминатор в конце
    out[need] = '\0';
    return true;
}


// Преобразует символ цифры в его числовое значение.
// Пример: 'A' -> 10, 'F' -> 15, '3' -> 3.
// Если символ недопустим — возвращает -1.
static int char_to_val(char c) noexcept {
    if (c >= '0' && c <= '9') return c - '0';
    if (c >= 'A' && c <= 'F') return 10 + (c - 'A');
    return -1;
}

// Проверяет, что строка s содержит ТОЛЬКО допустимые символы для заданной системы счисления.
bool validate_digits_for_base(const char* s, int base) noexcept {
    if (!s || !*s) return false;               // если пустая строка или NULL — ошибка
    if (!is_supported_base(base)) return false;// база должна быть 2, 8, 10 или 16

    std::size_t i = 0;
    if (s[i] == '+' || s[i] == '-') {          // если первый символ — знак
        ++i;
        if (s[i] == '\0') return false;        // один только знак — не число
    }

    bool has_digit = false;
    for (; s[i] != '\0'; ++i) {                // идём по каждому символу
        unsigned char uc = static_cast<unsigned char>(s[i]);
        if (!std::isalnum(uc)) return false;   // не буква/цифра — ошибка
        int v = char_to_val(s[i]);             // переводим символ в число
        if (v < 0 || v >= base) return false;  // цифра не входит в диапазон этой базы
        has_digit = true;
    }
    return has_digit;
}



// Переводит строку s_in из системы base в десятичное число (long long).
bool from_base_string(const char* s_in, int base, long long* out_value) noexcept {
    if (!out_value) return false;
    *out_value = 0; // обнуляем результат

    if (!is_supported_base(base)) return false;

    // Создаём временный буфер, чтобы очистить строку (обрезать пробелы и привести к верхнему регистру)
    char buf[128];
    if (!clean_input(s_in, buf, sizeof(buf))) return false;
    const char* s = buf;

    // Проверяем, что символы допустимы
    if (!validate_digits_for_base(s, base)) return false;

    // Разбираем знак
    int sign = 1;
    std::size_t i = 0;
    if (s[i] == '+' || s[i] == '-') {
        if (s[i] == '-') sign = -1;
        ++i;
    }

    // Теперь идём по цифрам и вычисляем acc = acc*base (+/-) digit
    long long acc = 0;
    for (; s[i] != '\0'; ++i) {
        int d = char_to_val(s[i]);

        if (sign > 0) {                        // положительное число
            if (acc > LLONG_MAX / base) return false;  // проверка на переполнение при умножении
            long long t = acc * base;
            if (d > 0 && t > LLONG_MAX - d) return false; // переполнение при сложении
            acc = t + d;
        } else {                               // отрицательное число
            if (acc < LLONG_MIN / base) return false;
            long long t = acc * base;
            if (d > 0 && t < LLONG_MIN + d) return false;
            acc = t - d;
        }
    }

    *out_value = acc;  // сохраняем результат
    return true;
}


// Переводит десятичное значение (value) в строку в системе base (2,8,10,16).
bool to_base_string(long long value, int base, char* out, std::size_t out_sz) noexcept {
    if (!out || out_sz == 0) return false;
    if (!is_supported_base(base)) return false;

    char tmp[70];      // временный буфер для записи цифр в обратном порядке
    std::size_t pos = 0;

    // === Случай 10-ой системы ===
    if (base == BASE_DEC) {
        if (value == 0) {
            if (out_sz < 2) return false;
            out[0] = '0'; out[1] = '\0';
            return true;
        }
        bool neg = value < 0;
        // unsigned long long нужен, чтобы корректно работать с отрицательными (через модуль)
        unsigned long long x = neg ? static_cast<unsigned long long>(-(value + 1)) + 1ULL
                                   : static_cast<unsigned long long>(value);
        while (x > 0ULL && pos + 1 < sizeof(tmp)) {
            int d = static_cast<int>(x % 10ULL);
            tmp[pos++] = static_cast<char>('0' + d);
            x /= 10ULL;
        }
        if (neg) tmp[pos++] = '-';

        // Проверяем, поместится ли в out
        if (pos + 1 > out_sz) return false;

        // Переворачиваем порядок цифр
        for (std::size_t i = 0; i < pos; ++i)
            out[i] = tmp[pos - 1 - i];
        out[pos] = '\0';
        return true;
    }

    // === Остальные системы (2, 8, 16) ===
    if (value == 0) {
        if (out_sz < 2) return false;
        out[0] = '0'; out[1] = '\0';
        return true;
    }

    bool neg = value < 0;
    unsigned long long x = neg ? static_cast<unsigned long long>(-(value + 1)) + 1ULL
                               : static_cast<unsigned long long>(value);

    while (x > 0ULL && pos + 1 < sizeof(tmp)) {
        int d = static_cast<int>(x % static_cast<unsigned long long>(base));
        // цифры 0–9 и буквы A–F
        char c = (d < 10) ? static_cast<char>('0' + d)
                          : static_cast<char>('A' + (d - 10));
        tmp[pos++] = c;
        x /= static_cast<unsigned long long>(base);
    }
    if (neg) tmp[pos++] = '-';

    if (pos + 1 > out_sz) return false;

    // Переворачиваем цифры в правильный порядок
    for (std::size_t i = 0; i < pos; ++i)
        out[i] = tmp[pos - 1 - i];
    out[pos] = '\0';
    return true;
}

/*
Как она работает:

Берёт остаток от деления value % base → это последняя цифра.

Сохраняет её в массив tmp[].

Делит число на основание: value = value / base.

Повторяет, пока не дойдёт до 0.

Потом переворачивает цифры (потому что шли с конца).

Если число отрицательное — добавляет '-'.


42 % 2 = 0
21 % 2 = 1
10 % 2 = 0
5  % 2 = 1
2  % 2 = 0
1  % 2 = 1


получили 010101, переворачиваешь → 101010.
*/


} // namespace basecalc
