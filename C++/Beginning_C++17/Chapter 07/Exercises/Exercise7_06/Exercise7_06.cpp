// Copyright (c) 2020 Cody R. Drisko. All rights reserved.
// Licensed under the MIT License. See the LICENSE file in the project root for more information.
//
// Name: Exercise7_06.cpp - Version 1.0.0
// Author: cdrisko
// Date: 08/05/2020-07:59:15
// Description: Finding all words that begin with a letter from a list of letters

#include <cctype>
#include <iostream>
#include <string>
#include <vector>

int main()
{
    std::string text;
    std::cout << "Enter some text terminated by *:\n";
    std::getline(std::cin, text, '*');

    std::string letters;
    std::cout << "Enter one or more letters (no spaces): ";
    std::cin  >> letters;

    std::vector<std::string> words, outputWords;

    const std::string separators { " ,;:.\"!?'\n" };
    std::size_t start { text.find_first_not_of(separators) };

    while (start != std::string::npos)
    {
        std::size_t end = text.find_first_of(separators, start + 1);
        if (end == std::string::npos)
            end = text.length();

        words.push_back(text.substr(start, end - start));
        start = text.find_first_not_of(separators, end + 1);
    }

    for (auto& ch : letters)
    {
        ch = std::tolower(ch);

        for (const auto& word : words)
        {
            if (std::tolower(word[0]) == ch)
                outputWords.push_back(word);
        }
    }

    std::cout << "The following words matched one of the letters passed to the second input: " << std::endl;

    int count {};

    for (const auto& word : outputWords)
    {
        std::cout << word << " ";

        if (++count == 5)
        {
            std::cout << std::endl;
            count = 0;
        }
    }

    std::cout << std::endl;
}
