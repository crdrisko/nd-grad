// Name: Ex4_08A.cpp - Version 1.0.0
// Author: cdrisko
// Date: 04/25/2020-12:36:50
// Description: Using return to exit a stitch statement (and the program)

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
            return 0;
        }

        std::cout << "You entered a consonant." << std::endl;
    }
    else
    {
        std::cout << "You did not enter a letter." << std::endl;
    }
}
