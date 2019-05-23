/***************************************************************\ 
|* Name: Ex4_03A.cpp                                           *|
|* Author: crdrisko                                            *|
|* Description: Using a nested if with cctype                  *|
|*                                                             *|
|*                                                             *|
|* Complile Command: g++ Ex4_03A.cpp -o Ex4_03A.out -std=c++17 *|
\***************************************************************/

#include <iostream>
#include <cctype>

int main()
{
    char letter {};                             // Store input here
    std::cout << "Enter a letter: ";            // Prompt for the input
    std::cin  >> letter;

    if (std::isupper(letter))
    {
        std::cout << "You entered an uppercase letter." << std::endl;
        return 0;
    }

    if (std::islower(letter))
    {
        std::cout << "You entered a lowercase letter." <<std::endl;
        return 0;
    }
    
    std::cout << "You did not enter a letter." << std::endl;    
}