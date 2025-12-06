#include "../include/playlist.hpp"

#include <cstring>  // strlen, strcpy, strcmp
#include <ostream>  // std::ostream

// Вспомогательная функция: дублирует C-строку в динамической памяти, чтобы не было проблем с временем жизни строки
namespace {
    char* duplicateString(const char* src){
        if (src == nullptr){
            return nullptr;
        }
        std::size_t len = std::strlen(src);
        char* dest = new char[len + 1];
        std::strcpy(dest, src);
        return dest;
    }

    // Вывести одну песню (в формате M:SS) в поток
    void printSongLine(std::ostream& out, const Song& song) {    
        int minutes = song.duration / 60;
        int seconds = song.duration % 60;

        out << "Песня: " << song.title
            << ", Исполнитель: " << song.artist
            << ", Длительность: " << minutes << ":";

        if (seconds < 10) {
            out << "0";    
        }
        out << seconds << "\n";
    }
}

// Добавить песню в конец плейлиста
Node* addSongToEnd(Node* head, const char* title, const char* artist, int duration) {
    Node* newNode = new Node;       // создаём новый узел
    newNode->data.title = duplicateString(title);           
    newNode->data.artist = duplicateString(artist);     
    newNode->data.duration = duration;
    newNode->next = nullptr;

    if (head == nullptr){
        // Список был пуст
        return newNode;
    }

    Node* current = head;
    while (current->next != nullptr){
        current = current->next;
    }
    current->next = newNode;
    return head;
}

// Удалить песню по названию 
void deleteSongByTitle(Node*& head, const char* title) {
    if (head == nullptr){
        return;
    }

    // Удаление в начале списка
    if (std::strcmp(head->data.title, title) == 0) {        // совпадение в голове списка
        Node* temp = head;      // временный указатель на удаляемый узел
        head = head->next;          // сдвигаем голову списка

        delete[] temp->data.title;         
        delete[] temp->data.artist;
        delete temp;
        return;
    }

    Node* current = head;
    Node* prev = nullptr;

    while (current != nullptr && std::strcmp(current->data.title, title) != 0)  {
        prev = current;
        current = current->next;
    }

    if (current == nullptr) {
        // Песня с таким названием не найдена
        return;
    }

    // current указывает на узел, который нужно удалить
    prev->next = current->next;

    delete[] current->data.title;
    delete[] current->data.artist;
    delete current;
}

// Найти самую длинную песню
Node* findLongestSong(Node* head)   {
    if (head == nullptr) {
        return nullptr;
    }

    Node* maxNode = head;       // Изначально самая длинная песня — первая
    Node* current = head->next;         // Начинаем со второго узла

    while (current != nullptr) {
        if (current->data.duration > maxNode->data.duration){
            maxNode = current;
        }
        current = current->next;
    }

    return maxNode;
}

// Общая длительность
int calculateTotalDuration(Node* head) {
    int total = 0;
    Node* current = head;
    while (current != nullptr){
        total += current->data.duration;
        current = current->next;
    }
    return total;
}

// Вывести плейлист в файл/поток
void printPlaylistToFile(Node* head, std::ostream& out){
    out << "Плейлист:\n";
    Node* current = head;
    while (current != nullptr) {
        printSongLine(out, current->data);
        current = current->next;
    }
}

// Очистить весь список
void clearList(Node*& head) {
    Node* current = head;
    while (current != nullptr){
        Node* next = current->next;

        delete[] current->data.title;
        delete[] current->data.artist;
        delete current;

        current = next;
    }
    head = nullptr;
}
