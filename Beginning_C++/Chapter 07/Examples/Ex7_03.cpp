/*************************************************************\ 
|* Name: Ex7_03.cpp                                          *|
|* Author: crdrisko                                          *|
|* Description: Comparing strings                            *|
|*                                                           *|
|*                                                           *|
|* Complile Command: g++ Ex7_03.cpp -o Ex7_03.out -std=c++17 *|
\*************************************************************/

#include <iostream>                     // For stream I/O
#include <iomanip>                      // For stream manipulators
#include <cctype>                       // For character conversion
#include <vector>                       // For vector container
#include <string>                       // For the string type

int main()
{
    std::vector<std::string> names;     // Vector of names
    std::string input_name;             // Stores a name
    char answer {};                     // Response to a prompt

    do
    {
        std::cout << "Enter a name: ";
        std::cin  >> input_name;        // Read a name and ...
        names.push_back(input_name);    // ... add it to the vector
        std::cout << "Do you want to enter another name? (y/n): ";
        std::cin  >> answer;
    } while (std::tolower(answer) == 'y');

    // Sort the names in ascending sequence
    bool sorted {};
    do 
    {
        sorted = true;                  // remains true when names are sorted
        for (size_t i {1}; i < names.size(); ++i)
        {
            if (names[i-1] > names[i])
            {                           // Out of order - so swap names
                names[i].swap(names[i-1]);
                sorted = false;
            }
        }
    } while (!sorted);

    // Find the length of the longest name
    size_t max_length {};
    for (const auto& name : names)
        if (max_length < name.length())
            max_length = name.length();
    
    // Output the sorted names 5 to a line
    const size_t field_width = max_length + 2;
    size_t count {};

    std::cout << "In ascending sequence the names you entered are:\n";
    for (const auto& name : names)
    {
        std::cout << std::setw(field_width) << name;
        if (!(++count % 5)) std::cout << std::endl;
    }

    std::cout << std::endl;
}