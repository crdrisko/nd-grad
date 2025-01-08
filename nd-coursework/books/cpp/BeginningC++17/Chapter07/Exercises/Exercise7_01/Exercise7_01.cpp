// Copyright (c) 2019-2025 Cody R. Drisko. All rights reserved.
// Licensed under the MIT License. See the LICENSE file in the project root for more information.
//
// Name: Exercise7_01.cpp
// Author: crdrisko
// Date: 07/25/2020-08:17:49
// Description: Calculating and outputting the average grade from an unknown number of students in a class

#include <cctype>
#include <cmath>
#include <iostream>
#include <string>
#include <vector>

int main()
{
    enum class Grades : char
    {
        A = 'A',
        B = 'B',
        C = 'C',
        D = 'D',
        F = 'F'
    };

    std::vector<std::string> studentNames;
    std::string currentName {};

    std::vector<Grades> studentGrades;
    char currentGrade {};

    char answer {};

    do
    {
        std::cout << "Enter a student's first name: ";
        std::cin >> currentName;
        studentNames.push_back(currentName);

        std::cout << "What grade did " << currentName << " recieve in the class? ";
        std::cin >> currentGrade;

        switch (std::toupper(currentGrade))
        {
        case 'A':
        case 'B':
        case 'C':
        case 'D':
        case 'F':
            studentGrades.push_back(static_cast<Grades>(std::toupper(currentGrade)));
            break;
        default:
            std::cout << "Invalid grade entered, valid options are A, B, C, D, or F." << std::endl;
            return 1;
        }

        std::cout << "Do you want to enter another name? (y/n): ";
        std::cin >> answer;
    } while (std::tolower(answer) == 'y');

    double gradeSum {};
    int charToIntNormalization {static_cast<int>('F')};

    for (const auto& grade : studentGrades)
    {
        /* Here we're going to make the assumption that all letters of the alphabet have contiguous integer representations.
            If that holds, we can take figure out the integer representation of 'F' and subtract the current grade from it.
            Note that 'F' was chosen because we want the 'F's normalized representation to equal 1. */
        if (grade != Grades::F)
            gradeSum += charToIntNormalization - static_cast<int>(grade);
        else
            gradeSum += 1;
    }

    Grades averageGrade = static_cast<Grades>(charToIntNormalization - std::round(gradeSum / studentGrades.size()));

    std::cout << "The average grade for the class was " << std::string {(averageGrade == Grades::A) ? "an " : "a "}
              << static_cast<char>(averageGrade) << std::endl;

    for (std::size_t i {}, count {}; i < studentNames.size(); ++i)
    {
        std::cout << studentNames[i] << " - " << static_cast<char>(studentGrades[i]) << '\t';

        if (++count == 3)
        {
            std::cout << std::endl;
            count = 0;
        }
    }

    std::cout << std::endl;
}
