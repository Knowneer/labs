#pragma once

// Сумма элементов массива
int recursiveSum(const int* arr, int size, int index = 0);
// Максимальный элемент
int recursiveMax(const int* arr, int size, int index = 0);
// Проверка, отсортирован ли массив
bool isSorted(const int* arr, int size, int index = 0);
// Вывод массива в обратном порядке
void printReverse(const int* arr, int size, int index = 0);
// Бинарный поиск (усложнение)
int binarySearchRecursive(const int* arr, int left, int right, int target);
