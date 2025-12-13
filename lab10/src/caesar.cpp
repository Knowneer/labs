#include "../include/caesar.hpp"
#include <cctype>
#include <map>
#include <string>

// --- Шифрование C-строки ---
void encryptC(const char* input, char* output, int shift)
{
    int i = 0;
    shift %= 26;

    for (; input[i] != '\0'; i++) {
        char c = input[i];

        if (std::isalpha(static_cast<unsigned char>(c))) {      // isalpha проверяет, является ли символ буквой
            char base = std::islower(c) ? 'a' : 'A';       // islower проверяет, является ли символ строчной буквой чтобы не сломать регистр
            output[i] = (c - base + shift + 26) % 26 + base;    // +26 чтобы не было отрицательных значений
        } else {
            output[i] = c;         
        }
    }

    output[i] = '\0';     
}

// --- Дешифрование C-строки ---
void decryptC(const char* input, char* output, int shift)
{
    int i = 0;
    shift %= 26;

    for (; input[i] != '\0'; i++) {
        char c = input[i];

        if (std::isalpha(static_cast<unsigned char>(c))) {
            char base = std::islower(c) ? 'a' : 'A';
            output[i] = (c - base - shift + 26) % 26 + base;
        } else {
            output[i] = c;
        }
    }

    output[i] = '\0';
}

// --- Частотный анализ ---
std::map<char, int> letterFrequency(const std::string& text){
    std::map<char, int> freq;

    for (char c : text) {
        if (std::isalpha(static_cast<unsigned char>(c))) {
            freq[std::tolower(c)]++;
        }
    }

    return freq;
}

// --- Взлом перебором ---
std::string bruteForce(const std::string& text)
{
    int bestShift = 0;
    int bestScore = -1;

    for (int shift = 0; shift < 26; shift++) {
        int score = 0;

        for (char c : text) {
            char lower = std::tolower(static_cast<unsigned char>(c));
            if (lower == 'e' || lower == 't' || lower == 'a' || lower == ' ') {
                score++;
            }
        }

        if (score > bestScore) {
            bestScore = score;
            bestShift = shift;
        }
    }

    std::string result;
    for (char c : text) {
        if (std::isalpha(static_cast<unsigned char>(c))) {
            char base = std::islower(c) ? 'a' : 'A';
            result += char((c - base - bestShift + 26) % 26 + base);
        } else {
            result += c;
        }
    }

    return result;
}
