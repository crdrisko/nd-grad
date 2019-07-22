/*************************************************************\ 
|* Name: Ex7_07.cpp                                          *|
|* Author: crdrisko                                          *|
|* Date: 05/16/19-12:35:44                                   *|
|* Description: Replacing words in a string                  *|
|*                                                           *|
|*                                                           *|
|* Complile Command: g++ Ex7_07.cpp -o Ex7_07.out -std=c++17 *|
\*************************************************************/

#include <iostream>
#include <string>

int main()
{
    std::string text;                                       // The string to be modified
    std::cout << "Enter a string terminated by *:\n";
    std::getline(std::cin, text, '*');

    std::string word;                                       // Word to be replaced
    std::cout << "Enter the word to be replaced: ";
    std::cin  >> word;

    std::string replacement;                                // The word to be substituted
    std::cout << "Enter the string to be substituted for " << word << ": ";
    std::cin  >> replacement;

    if (word == replacement)                                // Verify there's something to do
    {
        std::cout << "The word and its replacement are the same.\n"
                  << "Operation aborted." << std::endl;
        return 1;
    }
    size_t start {text.find(word)};
    while (start != std::string::npos)
    {
        text.replace(start, word.length(), replacement);    // Replace word
        start = text.find(word, start + replacement.length());
    }

    std::cout << "\nThe string you entered is now:\n" << text << std::endl;
}