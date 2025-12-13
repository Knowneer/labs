#include <iostream>
#include <fstream>
#include <string>
#include "../include/caesar.hpp"

int main()
{
    std::ifstream fin("input.txt");
    std::ofstream fout("output.txt");

    if (!fin.is_open()) {
        std::cerr << "Невозможно открыть файл input.txt\n";
        return 1;
    }

    int shift;
    std::string textEncrypt;
    std::string textDecrypt;

    fin >> shift;           // читаем сдвиг из файла 
    fin.ignore(); // убрать '\n' после числа
    std::getline(fin, textEncrypt);
    std::getline(fin, textDecrypt);
    
    int encryptedlen = textEncrypt.length() + 1;
    int decryptedlen = textDecrypt.length() + 1;        


    char encrypted[encryptedlen] = {};
    char decrypted[decryptedlen] = {};

    encryptC(textEncrypt.c_str(), encrypted, shift);
    decryptC(textDecrypt.c_str(), decrypted, shift);

    auto freq = letterFrequency(textEncrypt);

    fout << "Шифрование шифром Цезаря:\n\n";
    fout << "Исходный текст: " << textEncrypt << "\n";
    fout << "Сдвиг: " << shift << "\n";
    fout << "Зашифрованный текст: " << encrypted << "\n\n";

    fout << "Текст для расшифровки: " << textDecrypt << "\n";
    fout << "Сдвиг: " << shift << "\n";
    fout << "Расшифрованный текст: " << decrypted << "\n\n";

    fout << "Частота букв в исходном тексте:\n";
    for (const auto& [letter, count] : freq) {
        fout << letter << ": " << count << "\n";
    }

    fout << "\nПопытка взлома:\n";
    fout << bruteForce(textDecrypt) << "\n";

    return 0;
}
