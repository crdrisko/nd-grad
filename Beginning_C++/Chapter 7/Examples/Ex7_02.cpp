/*************************************************************\ 
|* Name: Ex7_02.cpp                                          *|
|* Author: crdrisko                                          *|
|* Description: Accessing characters in a string             *|
|*                                                           *|
|*                                                           *|
|* Complile Command: g++ Ex7_02.cpp -o Ex7_02.out -std=c++17 *|
\*************************************************************/

#include <iostream>
#include <cctype>
#include <string>

int main()
{
    std::string text;                               // Stores the input
    std::cout << "Enter a line of text:\n";
    std::getline(std::cin, text);                   // Read a line including spaces

    unsigned vowels {};                             // Count of vowels
    unsigned consonants {};                         // Count of consonants
    for (size_t i {}; i < text.length(); ++i)
    {
        if (std::isalpha(text[i]))                  // Check for a letter
        {
            switch (std::tolower(text[i]))          // Convert to lowercase
            {
                case 'a': case 'e': case 'i': case 'o': case 'u':
                    ++vowels;
                    break;

                default:
                    ++consonants;
                    break;
            }
        }
    }

    std::cout << "Your input contained " << vowels << " vowels and "
              << consonants << " consonants." << std::endl;
}