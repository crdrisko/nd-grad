// Name: Ex4_08.cpp - Version 1.0.0
// Author: cdrisko
// Date: 04/25/2020-12:03:15
// Description: Multiple case actions

#include <cctype>
#include <iostream>

int main()
{
    char letter {};
    std::cout << "Enter a letter: ";
    std::cin  >> letter;

    if (std::isalpha(letter))
    {
        switch (std::tolower(letter))
        {
        case 'a': case 'e': case 'i': case 'o': case 'u':
            std::cout << "You entered a vowel." << std::endl;
            break;
        default:
            std::cout << "You entered a consonant." << std::endl;
            break;
        }
    }
    else
    {
        std::cout << "You did not enter a letter." << std::endl;
    }
}
