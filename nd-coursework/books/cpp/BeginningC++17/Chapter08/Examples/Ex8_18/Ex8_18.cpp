// Copyright (c) 2018 Ivor Horton and Peter Van Weert. Some rights reserved.
// Licensed under the Freeware License. See the LICENSE file in the project root for more information.
//
// Name: Ex8_18.cpp
// Author: crdrisko
// Date: 10/23/2020-07:30:56
// Description: The quicksort algorithm

#include <iomanip>
#include <iostream>
#include <memory>
#include <string>
#include <string_view>
#include <vector>

using Words = std::vector<std::shared_ptr<std::string>>;

void swap(Words& words, std::size_t first, std::size_t second);
void sort(Words& words);
void sort(Words& words, std::size_t start, std::size_t end);
void extract_words(Words& words, std::string_view text, std::string_view separators);
void show_words(const Words& words);
std::size_t max_word_length(const Words& words);

int main()
{
    Words words;
    std::string text;                      // The string to be sorted
    const auto separators {" ,.!?\"\n"};   // Word delimiters

    // Read the string to be searched from the keyboard
    std::cout << "Enter a string terminated by *:" << std::endl;
    getline(std::cin, text, '*');

    extract_words(words, text, separators);

    if (words.empty())
    {
        std::cout << "No words in text." << std::endl;
        return 0;
    }

    sort(words);         // Sort the words
    show_words(words);   // Output the words
}

void swap(Words& words, std::size_t first, std::size_t second)
{
    auto temp {words[first]};
    words[first]  = words[second];
    words[second] = temp;
}

void sort(Words& words)
{
    if (!words.empty())
        sort(words, 0, words.size() - 1);
}

void sort(Words& words, std::size_t start, std::size_t end)
{
    // start index must be less that end index for 2 or more elements
    if (!(start < end))
        return;

    // Choose middle address to partition set
    swap(words, start, (start + end) / 2);   // Swap middle address with start

    // Check words against chosen word
    std::size_t current {start};

    for (std::size_t i {start + 1}; i <= end; i++)
    {
        if (*words[i] < *words[start])   // Is word less than chosen word?
            swap(words, ++current, i);   // Yes, so swap to the left
    }

    swap(words, start, current);   // Swap chosen and last swapped words

    if (current > start)
        sort(words, start, current - 1);   // Sort left subset if exists
    if (end > current + 1)
        sort(words, current + 1, end);   // Sort right subset if exists
}

void extract_words(Words& words, std::string_view text, std::string_view separators)
{
    std::size_t start {text.find_first_not_of(separators)};   // Start 1st word
    std::size_t end {};                                       // Index for the end of a word

    while (start != std::string_view::npos)
    {
        end = text.find_first_of(separators, start + 1);   // Find end separator
        if (end == std::string_view::npos)                 // End of text?
            end = text.length();                           // Yes, so set to last + 1
        words.push_back(std::make_shared<std::string>(text.substr(start, end - start)));
        start = text.find_first_not_of(separators, end + 1);   // Find next word
    }
}

void show_words(const Words& words)
{
    const std::size_t field_width {max_word_length(words) + 1};
    const std::size_t words_per_line {8};

    std::cout << std::left << std::setw(field_width) << *words[0];   // Output the first word

    std::size_t words_in_line {};   // Words in current line

    for (std::size_t i {1}; i < words.size(); ++i)
    {
        // Output newline when initial letter changes or after 8 per line
        if ((*words[i])[0] != (*words[i - 1])[0] || ++words_in_line == words_per_line)
        {
            words_in_line = 0;
            std::cout << std::endl;
        }

        std::cout << std::setw(field_width) << *words[i];   // Output a word
    }

    std::cout << std::endl;
}

std::size_t max_word_length(const Words& words)
{
    std::size_t max {};

    for (auto& pword : words)
        if (max < pword->length())
            max = pword->length();
    return max;
}
