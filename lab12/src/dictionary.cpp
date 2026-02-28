#include "../include/dictionary.hpp"
#include <iostream>

void addWord(std::map<std::string, std::string>& dict)
{
    std::string eng, rus;

    std::cout << "Введите слово на английском: ";
    std::cin >> eng;

    std::cout << "Введите перевод: ";
    std::cin >> rus;

    dict[eng] = rus;            // Добавление или обновление слова в словаре
    std::cout << "Слово добавлено!\n";
}

void translateWord(const std::map<std::string, std::string>& dict)
{
    std::string word;
    std::cout << "Введите слово: ";
    std::cin >> word;

    auto it = dict.find(word);          
    if (it != dict.end())           
        std::cout << "Перевод: " << it->second << "\n";             
    else
        std::cout << "Слово \"" << word << "\" не найдено в словаре!\n";
}

void removeWord(std::map<std::string, std::string>& dict)
{
    std::string word;
    std::cout << "Введите слово для удаления: ";
    std::cin >> word;

    if (dict.erase(word))       //возвращает 1, если слово удалено успешно, иначе 0
        std::cout << "Слово удалено!\n";
    else
        std::cout << "Такого слова нет в словаре!\n";
}

void showDictionary(const std::map<std::string, std::string>& dict)
{
    if (dict.empty()) {      // Проверка на пустой словарь
        std::cout << "Словарь пуст.\n";
        return;
    }

    std::cout << "Весь словарь:\n";
    for (const auto& pair : dict)
        std::cout << pair.first << " - " << pair.second << "\n";        // Вывод всех слов и их переводов
}

bool containsWord(const std::map<std::string, std::string>& dict, const std::string& word){
    return dict.find(word) != dict.end();       // если find не нашел слово, возвращается dict.end()
}
