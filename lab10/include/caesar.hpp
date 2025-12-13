#pragma once
#include <string>
#include <map>


// Шифр Цезаря — это когда каждую букву мы сдвигаем на N позиций по алфавиту.

void encryptC(const char* input, char* output, int shift);		//--- Шифрование C-строки
void decryptC(const char* input, char* output, int shift);		//--- Дешифрование C-строки

std::string bruteForce(const std::string& text);				//--- Взлом перебором

std::map<char, int> letterFrequency(const std::string& text);			//--- Частота букв в тексте
