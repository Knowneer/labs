#include "student_utils.hpp"

#include <iostream>
#include <fstream>
#include <iomanip>  // std::fixed, std::setprecision

namespace lab_students {

bool readGradesFromFile(const std::string& filename,
                        int grades[MAX_STUDENTS][GRADES_COUNT],
                        int& studentCount)
{
    std::ifstream in(filename);
    if (!in.is_open()) {
        std::cerr << "Ошибка: не удалось открыть файл \"" << filename << "\" для чтения.\n";
        return false;
    }

    if (!(in >> studentCount)) {
        std::cerr << "Ошибка: не удалось прочитать количество студентов из файла.\n";
        return false;
    }

    if (studentCount < 1 || studentCount > MAX_STUDENTS) {
        std::cerr << "Ошибка: некорректное количество студентов (" << studentCount
                  << "), допустимо от 1 до " << MAX_STUDENTS << ".\n";
        return false;
    }

    for (int i = 0; i < studentCount; ++i) {
        for (int j = 0; j < GRADES_COUNT; ++j) {
            if (!(in >> grades[i][j])) {
                std::cerr << "Ошибка: недостаточно данных для студента " << (i + 1)
                          << " (оценка №" << (j + 1) << ").\n";
                return false;
            }
        }
    }

    return true;
}

void computeAverages(const int grades[MAX_STUDENTS][GRADES_COUNT],
                     int studentCount,
                     double averages[MAX_STUDENTS])
{
    for (int i = 0; i < studentCount; ++i) {
        int sum = 0;
        for (int j = 0; j < GRADES_COUNT; ++j) {
            sum += grades[i][j];
        }
        averages[i] = static_cast<double>(sum) / GRADES_COUNT;
    }
}

int findMaxAverageIndex(const double averages[MAX_STUDENTS],
                        int studentCount)
{
    if (studentCount <= 0) {
        return -1;
    }

    int maxIndex = 0;
    for (int i = 1; i < studentCount; ++i) {
        if (averages[i] > averages[maxIndex]) {
            maxIndex = i;
        }
    }
    return maxIndex;
}

int countAboveThreshold(const double averages[MAX_STUDENTS],
                        int studentCount,
                        double threshold)
{
    int count = 0;
    for (int i = 0; i < studentCount; ++i) {
        if (averages[i] > threshold) {
            ++count;
        }
    }
    return count;
}

bool writeReportToFile(const std::string& filename,
                       const double averages[MAX_STUDENTS],
                       int studentCount,
                       int maxAvgIndex,
                       double threshold,
                       int countAbove)
{
    std::ofstream out(filename);
    if (!out.is_open()) {
        std::cerr << "Ошибка: не удалось открыть файл \"" << filename << "\" для записи.\n";
        return false;
    }

    out << "Средние баллы студентов:\n";
    out << std::fixed << std::setprecision(2);

    for (int i = 0; i < studentCount; ++i) {
        out << "Студент " << (i + 1) << ": " << averages[i] << '\n';
    }

    if (maxAvgIndex >= 0 && maxAvgIndex < studentCount) {
        out << "Студент с максимальным средним баллом: Студент "
            << (maxAvgIndex + 1) << " (" << averages[maxAvgIndex] << ")\n";
    } else {
        out << "Студент с максимальным средним баллом: не определён\n";
    }

    out << "Количество студентов с средним баллом выше "
        << threshold << ": " << countAbove << '\n';

    return true;
}

} // namespace lab_students
