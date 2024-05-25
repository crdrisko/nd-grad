// Copyright (c) 2019-2024 Cody R. Drisko. All rights reserved.
// Licensed under the MIT License. See the LICENSE file in the project root for more information.
//
// Name: Exercise7_03.cpp
// Author: cdrisko
// Date: 08/03/2020-07:52:32
// Description: Replacing all instances of a (full) word in a string with astrisks

#include <cctype>
#include <cstddef>
#include <iostream>
#include <string>
#include <vector>

int main()
{
    std::string text;
    std::cout << "Enter some text terminated by *:\n";
    std::getline(std::cin, text, '*');

    std::string replace, lowercaseReplace;
    std::cout << "Enter the word you'd like to be replaced: ";
    std::cin >> replace;

    for (const auto& ch : replace)
        lowercaseReplace.push_back(std::tolower(ch));

    const std::string separators {" ,;:.\"!?'\n"};
    std::size_t start {text.find_first_not_of(separators)};

    while (start != std::string::npos)
    {
        std::size_t end = text.find_first_of(separators, start + 1);
        if (end == std::string::npos)
            end = text.length();

        std::string word {text.substr(start, end - start)};
        std::string lowercaseWord {};

        for (const auto& ch : word)
            lowercaseWord.push_back(std::tolower(ch));

        if (lowercaseWord == lowercaseReplace)
            text.replace(start, replace.length(), replace.length(), '*');

        start = text.find_first_not_of(separators, end + 1);
    }

    std::cout << "Your string is now:\n" << text << std::endl;
}
