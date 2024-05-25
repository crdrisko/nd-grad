// Copyright (c) 2018 Ivor Horton and Peter Van Weert. Some rights reserved.
// Licensed under the Freeware License. See the LICENSE file in the project root for more information.
//
// Name: Ex7_05.cpp
// Author: cdrisko
// Date: 05/03/2020-16:55:28
// Description: Searching within substrings

#include <iostream>
#include <string>

int main()
{
    std::string text;   // The string to be searched
    std::string word;   // Substring to be found
    std::cout << "Enter the string to be searched and press Enter:\n";
    std::getline(std::cin, text);

    std::cout << "Enter the string to be found and press Enter:\n";
    std::getline(std::cin, word);

    std::size_t count {};   // Count of substring occurences
    std::size_t index {};   // String index
    while ((index = text.find(word, index)) != std::string::npos)
    {
        ++count;
        index += word.length();
    }

    std::cout << "Your text contained " << count << " occurences of \"" << word << "\"." << std::endl;
}
