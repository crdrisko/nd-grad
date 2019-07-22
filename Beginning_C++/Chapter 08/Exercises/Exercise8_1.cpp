/***********************************************************************\ 
|* Name: Exercise8_1.cpp                                               *|
|* Author: crdrisko                                                    *|
|* Date: 06/05/19-14:15:02                                             *|
|* Description: Prompts for and outputs the user's vaild DOB           *|
|*                                                                     *|
|*                                                                     *|
|* Complile Command: g++ Exercise8_1.cpp -o Exercise8_1.out -std=c++17 *|
\***********************************************************************/

#include <iostream>
#include <iomanip>
#include <vector>
#include <string>
#include <array>
#include <cmath>
#include <cctype>
#include <limits>
#include <memory>
#include <sstream>
#include <string_view>
#include <optional>

int validate_input(int lower, int upper, std::string_view description);
int year();
int month();
int day();


int main()
{
    
}

int validate_input(int lower, int upper, std::string_view description)
{
    int input {};
    std::cout << "Enter a " << description << " between " << lower << " and " 
              << upper << "." << std::endl;
    std::cin  >> input;

    while (input < lower || input > upper)
    {
        std::cout << "Please enter a valid integer: ";
        std::cin  >> input;
    }
    return input;
}