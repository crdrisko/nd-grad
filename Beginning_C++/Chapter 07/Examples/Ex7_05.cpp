/*************************************************************\ 
|* Name: Ex7_05.cpp                                          *|
|* Author: crdrisko                                          *|
|* Description: Searching within substrings                  *|
|*                                                           *|
|*                                                           *|
|* Complile Command: g++ Ex7_05.cpp -o Ex7_05.out -std=c++17 *|
\*************************************************************/

#include <iostream>
#include <string>

int main()
{
    std::string text;                           // The string to be searched
    std::string word;                           // Substring to be found
    std::cout << "Enter the string to be searched and press Enter:\n";
    std::getline(std::cin, text);

    std::cout << "Enter the string to be found and press Enter:\n";
    std::getline(std::cin, word);

    size_t count {};                            // Count of substring occurences
    size_t index {};                            // String index
    while ((index = text.find(word, index)) != std::string::npos)
    {
        ++count;
        index += word.length();
    }

    std::cout << "Your text contained " << count << " occurrences of \""
              << word << "\"." << std::endl;
}