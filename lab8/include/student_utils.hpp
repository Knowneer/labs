#pragma once

#include <string>

namespace lab_students {

constexpr int MAX_STUDENTS = 50;
constexpr int GRADES_COUNT = 5;

bool readGradesFromFile(const std::string& filename,
                        int grades[MAX_STUDENTS][GRADES_COUNT],
                        int& studentCount);

void computeAverages(const int grades[MAX_STUDENTS][GRADES_COUNT],
                     int studentCount,
                     double averages[MAX_STUDENTS]);

int findMaxAverageIndex(const double averages[MAX_STUDENTS],
                        int studentCount);

int countAboveThreshold(const double averages[MAX_STUDENTS],
                        int studentCount,
                        double threshold);

bool writeReportToFile(const std::string& filename,
                       const double averages[MAX_STUDENTS],
                       int studentCount,
                       int maxAvgIndex,
                       double threshold,
                       int countAbove);

} // namespace lab_students
