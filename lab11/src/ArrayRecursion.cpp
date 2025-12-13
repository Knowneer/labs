#include "../include/ArrayRecursion.hpp"
#include <iostream>

// --- Сумма элементов ---
int recursiveSum(const int* arr, int size, int index){
    if (index == size)			 
        return 0;

    return arr[index] + recursiveSum(arr, size, index + 1);
}

// --- Максимальный элемент ---
int recursiveMax(const int* arr, int size, int index){
    if (index == size - 1)		
        return arr[index];

    int maxOfRest = recursiveMax(arr, size, index + 1);
    return arr[index] > maxOfRest ? arr[index] : maxOfRest;
}

// --- Проверка сортировки ---
bool isSorted(const int* arr, int size, int index){
    if (index >= size - 1)
        return true;

    if (arr[index] > arr[index + 1])
        return false;

    return isSorted(arr, size, index + 1);
}

// --- Вывод в обратном порядке ---
void printReverse(const int* arr, int size, int index){
    if (index == size)
        return;

    printReverse(arr, size, index + 1);
    std::cout << arr[index] << " ";
}

// --- Бинарный поиск ---
int binarySearchRecursive(const int* arr, int left, int right, int target){
    if (left > right) //если левая граница ушла правее правой — диапазон пуст - элемента НЕТ
        return -1;

    int mid = (left + right) / 2;

    if (arr[mid] == target)
        return mid;

    if (target < arr[mid])
        return binarySearchRecursive(arr, left, mid - 1, target);
    else
        return binarySearchRecursive(arr, mid + 1, right, target);
}
