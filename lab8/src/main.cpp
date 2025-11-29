#include <iostream>
#include <string>
#include "../include/student_utils.hpp"

int main()
{


	const std::string inputFileName  = "data/input.txt";
	const std::string outputFileName = "data/output.txt";
    const double threshold = 4.0;

    int grades[lab_students::MAX_STUDENTS][lab_students::GRADES_COUNT] = {};    
    double averages[lab_students::MAX_STUDENTS] = {};
    int studentCount = 0;

    if (!lab_students::readGradesFromFile(inputFileName, grades, studentCount)) {
        std::cerr << "Завершение программы из-за ошибки чтения входного файла.\n";
        return 1;
    }

    lab_students::computeAverages(grades, studentCount, averages);

    int maxIndex = lab_students::findMaxAverageIndex(averages, studentCount);
    int countAbove = lab_students::countAboveThreshold(averages, studentCount, threshold);

    if (!lab_students::writeReportToFile(outputFileName, averages, studentCount,
                                         maxIndex, threshold, countAbove)) {
        std::cerr << "Завершение программы из-за ошибки записи отчёта.\n";
        return 1;
    }

    std::cout << "Отчёт успешно записан в файл \"" << outputFileName << "\".\n";
    return 0;
}
