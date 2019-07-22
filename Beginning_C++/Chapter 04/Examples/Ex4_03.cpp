/*************************************************************\ 
|* Name: Ex4_03.cpp                                          *|
|* Author: crdrisko                                          *|
|* Description: Using a nested if                            *|
|*                                                           *|
|*                                                           *|
|* Complile Command: g++ Ex4_03.cpp -o Ex4_03.out -std=c++17 *|
\*************************************************************/

#include <iostream>
#include <cmath>

int main()
{
    char letter {};                             // Store input here
    std::cout << "Enter a letter: ";            // Prompt for the input
    std::cin  >> letter;

    if (letter >= 'A')
    {                                           // letter is 'A' or larger
        if (letter <= 'Z')
        {
            std::cout << "You entered an uppercase letter." << std::endl;
            return 0;
        }
    }

    if (letter >= 'a')                          // Test for 'a' or larger
        if (letter <= 'z')
        {                                       // letter is >= 'a' and <= 'z'
            std::cout << "You entered a lowercase letter." <<std::endl;
            return 0;
        }
    std::cout << "You did not enter a letter." << std::endl;    
}