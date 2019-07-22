/***********************************************************************\ 
|* Name: Exercise7_1.cpp                                               *|
|* Author: crdrisko                                                    *|
|* Date: 05/20/19-13:26:01                                             *|
|* Description: Grade calculator for an unknown number of students     *|
|*                                                                     *|
|*                                                                     *|
|* Complile Command: g++ Exercise7_1.cpp -o Exercise7_1.out -std=c++17 *|
\***********************************************************************/

#include <iostream>
#include <cmath>
#include <iomanip>
#include <cctype>
#include <vector>
#include <string>

int main()
{
    std::vector<std::string> names;
    std::vector<char> grades;
    std::string input_name;
    char input_grade {};
    char answer {};

    do
    {
        std::cout << "Enter the name of a student: ";
        std::cin  >> input_name;
        names.push_back(input_name);

        if (input_name.find_last_of('s') == input_name.length() - 1)
            std::cout << "Enter " << input_name << "' letter grade: ";
        else
            std::cout << "Enter " << input_name << "'s letter grade: ";
        std::cin  >> input_grade;
        grades.push_back(input_grade);

        std::cout << "Would you like to enter another name? (y/n): ";
        std::cin  >> answer;
    } while (std::tolower(answer) == 'y');
    
    std::vector<unsigned int> number_grades;
    float average {};

    for (size_t i {}; i < grades.size(); ++i)
    {
        switch (std::toupper(grades[i]))             // Assigns numerical values to letter grades
        {
            case 'A':
                number_grades.push_back(5);
                break;
            case 'B':
                number_grades.push_back(4);
                break;
            case 'C':
                number_grades.push_back(3);
                break;
            case 'D':
                number_grades.push_back(2);
                break;
            case 'F':
                number_grades.push_back(1);
                break;
            default:
                if (input_name.find_last_of('s') == input_name.length() - 1)
                    std::cout << names[i] << "' grade was not A, B, C, D, or F." << std::endl;
                else
                    std::cout << names[i] << "'s grade was not A, B, C, D, or F." << std::endl;
                return 0;
        }
        average += number_grades[i];
        average /= number_grades.size();
    }

    char avg_grade {};
    switch (static_cast<int>(std::round(average)))   // Reassigns the letter grade   
    {
        case 1:
            avg_grade = 'F';
            break;
        case 2:
            avg_grade = 'D';
            break;
        case 3:
            avg_grade = 'C';
            break;
        case 4:
            avg_grade = 'B';
            break;
        case 5: case 6:
            avg_grade = 'A';
            break;
    }
    std::cout << "The average grade for the class was a " << avg_grade << "." << std::endl;
    size_t max_length {};
    for (const auto& name : names)
    {
        if (max_length < name.length())
            max_length = name.length();
    }
    const size_t field_width = max_length + 2;
    size_t count {};

    std::cout << "These are the students you entered and their grades:\n";
    for (size_t i {}; i < grades.size(); ++i)
    {
        std::cout << std::setw(field_width) << names[i] << ": (" << std::toupper(grades[i]) << ")";
        if (!(++count % 3)) std::cout << std::endl;
    }
    std::cout << std::endl;
}
