#include <iostream>
#include <map>
#include <string>

#include "../include/dictionary.hpp"

int main()
{
    std::map<std::string, std::string> dictionary;
    int choice;

    std::cout << "=== Англо-русский словарь ===\n";

    do
    {
        std::cout << "\nМеню:\n";
        std::cout << "1. Добавить слово\n";
        std::cout << "2. Перевести слово\n";
        std::cout << "3. Удалить слово\n";
        std::cout << "4. Показать весь словарь\n";
        std::cout << "0. Выход\n";
        std::cout << "Выберите действие: ";
        std::cin >> choice;

        switch (choice)
        {
        case 1:
            addWord(dictionary);
            break;
        case 2:
            translateWord(dictionary);
            break;
        case 3:
            removeWord(dictionary);
            break;
        case 4:
            showDictionary(dictionary);
            break;
        case 0:
            std::cout << "Выход из программы.\n";
            break;
        default:
            std::cout << "Неверный пункт меню!\n";
        }

    } while (choice != 0);

    return 0;
}
