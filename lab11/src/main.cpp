#include <iostream>
#include "../include/ArrayRecursion.hpp"

int main()
{
    std::cout << "=== Рекурсивная обработка массива ===\n\n";

    int n;
    std::cout << "Введите размер массива: ";
    std::cin >> n;

    int* arr = new int[n];

    std::cout << "Введите элементы массива: ";
    for (int i = 0; i < n; i++) {
        std::cin >> arr[i];
    }

    std::cout << "\nИсходный массив: [";
    for (int i = 0; i < n; i++) {
        std::cout << arr[i];
        if (i != n - 1) std::cout << ", ";
    }
    std::cout << "]\n\n";

    std::cout << "Сумма элементов: "
              << recursiveSum(arr, n) << "\n";

    std::cout << "Максимальный элемент: "
              << recursiveMax(arr, n) << "\n";

    std::cout << "Массив отсортирован? "
              << (isSorted(arr, n) ? "Да" : "Нет") << "\n\n";

    std::cout << "Массив в обратном порядке: [";
    printReverse(arr, n);
    std::cout << "]\n\n";


    int* copy = new int[n];
    for (int i = 0; i < n; i++)
        copy[i] = arr[i];

    std::cout << "Исходный массив отсортирован? "
            << (isSorted(copy, n) ? "Да" : "Нет") << "\n";

    int* reversed = new int[n];
    for (int i = 0; i < n; i++)
        reversed[i] = arr[n - 1 - i];

    std::cout << "Реверс-массив отсортирован? "
            << (isSorted(reversed, n) ? "Да" : "Нет") << "\n";

        // Бинарный поиск
        int* sortedArr = new int[n];

// копируем исходный массив
    for (int i = 0; i < n; i++)
        sortedArr[i] = arr[i];

// простая сортировка (пузырёк)
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (sortedArr[j] > sortedArr[j + 1]) {
                int tmp = sortedArr[j];
                sortedArr[j] = sortedArr[j + 1];
                sortedArr[j + 1] = tmp;
            }
        }
    }

    int target;
    std::cout << "Введите число для бинарного поиска: ";
    std::cin >> target;

    int index = binarySearchRecursive(sortedArr, 0, n - 1, target);

    if (index != -1)
        std::cout << "Элемент найден на позиции: " << index << "\n";
    else
        std::cout << "Элемент не найден\n";

    delete[] arr;
    delete[] sortedArr;

    return 0;
}
