// Copyright (c) 2019-2024 Cody R. Drisko. All rights reserved.
// Licensed under the MIT License. See the LICENSE file in the project root for more information.
//
// Name: Exercise7_02.cpp
// Author: cdrisko
// Date: 08/02/2020-13:27:53
// Description: Determining all unique words from a user's input over an arbitrary number of lines

#include <iomanip>
#include <iostream>
#include <string>
#include <vector>

int main()
{
    std::string text;
    std::cout << "Enter some text terminated by *:\n";
    std::getline(std::cin, text, '*');

    std::vector<std::string> words;
    std::vector<unsigned int> counts;

    std::size_t maxLength {};

    const std::string separators {" ,;:.\"!?'\n"};
    std::size_t start {text.find_first_not_of(separators)};

    while (start != std::string::npos)
    {
        std::size_t end = text.find_first_of(separators, start + 1);
        if (end == std::string::npos)
            end = text.length();

        bool wordMatch {false};
        std::string currentWord {text.substr(start, end - start)};

        // Determine if the word has already been added to the vector
        for (std::size_t i {}; i < words.size(); ++i)
        {
            if (currentWord == words[i])
            {
                wordMatch = true;
                ++counts[i];
                break;
            }
        }

        if (!wordMatch)
        {
            words.push_back(currentWord);
            counts.push_back(1);
        }

        start = text.find_first_not_of(separators, end + 1);
    }

    // Determine max length for formatting purposes
    for (const auto& word : words)
        if (word.length() > maxLength)
            maxLength = word.length();

    // Output the data 3 to a line, left aligned for the word, right aligned for the count
    for (std::size_t i {}, count {}; i < words.size(); ++i)
    {
        std::cout << std::setw(maxLength) << std::left << std::setw(maxLength) << words[i] << std::setw(4) << std::right
                  << counts[i] << " ";

        if (++count == 3)
        {
            std::cout << std::endl;
            count = 0;
        }
    }

    std::cout << std::endl;
}
