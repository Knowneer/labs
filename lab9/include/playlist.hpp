#pragma once

#include <iosfwd> // объявление std::ostream

// Структура песни
struct Song	{
    char* title;    // название
    char* artist;   // исполнитель
    int duration;   // длительность в секундах
};

// односвязный список узлов
struct Node	{ 	 	
    Song data;
    Node* next;		
};

// Добавить песню в конец плейлиста
Node* addSongToEnd(Node* head, const char* title, const char* artist, int duration);

// Удалить песню по названию (первое вхождение)
void deleteSongByTitle(Node*& head, const char* title);

// Найти самую длинную песню (указатель на узел)
Node* findLongestSong(Node* head);

// Общая длительность плейлиста (в секундах)
int calculateTotalDuration(Node* head);

// Вывести плейлист в поток (можно ofstream, можно cout)
void printPlaylistToFile(Node* head, std::ostream& out);

// Очистить весь список
void clearList(Node*& head);

