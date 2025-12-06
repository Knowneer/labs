#include <iostream>
#include <fstream>
#include <string>

#include "../include/playlist.hpp"

int main()
{
    // Открываем входной файл
    std::ifstream fin("../input.txt");
    if (!fin.is_open()) {
        std::cerr << "Не удалось открыть input.txt\n";
        return 1;
    }

    // Открываем выходной файл
    std::ofstream fout("output.txt");
    if (!fout.is_open())
    {
        std::cerr << "Не удалось открыть output.txt\n";
        fin.close();
        return 1;
    }

    int n;
    fin >> n; // количество песен

    Node *head = nullptr;   // голова списка

    for (int i = 0; i < n; ++i) {
        std::string titleStr;
        std::string artistStr;
        int duration;

        fin >> titleStr >> artistStr >> duration;

        head = addSongToEnd(head, titleStr.c_str(), artistStr.c_str(), duration);
    }

    // Выводим плейлист
    printPlaylistToFile(head, fout);
    fout << "\n";

    // Находим самую длинную песню
    Node *longestNode = findLongestSong(head);
    if (longestNode != nullptr)
    {
        int minutes = longestNode->data.duration / 60;
        int seconds = longestNode->data.duration % 60;

        fout << "Самая длинная песня: " << longestNode->data.title
             << " (" << minutes << ":";

        if (seconds < 10)
        {
            fout << "0";
        }
        fout << seconds << ")\n";
    }
    else
    {
        fout << "Самая длинная песня: список пуст\n";
    }

    // Общая длительность
    int totalDuration = calculateTotalDuration(head);
    int totalMinutes = totalDuration / 60;
    int totalSeconds = totalDuration % 60;

    fout << "Общая длительность плейлиста: "
         << totalMinutes << ":";

    if (totalSeconds < 10)
    {
        fout << "0";
    }
    fout << totalSeconds << "\n";

    // Пример: можешь здесь протестировать deleteSongByTitle,
    // если препод требует использование всех функций.
    // Например:
    // deleteSongByTitle(head, "Imagine");

    // Чистим список
    clearList(head);

    fin.close();
    fout.close();

    return 0;
}
