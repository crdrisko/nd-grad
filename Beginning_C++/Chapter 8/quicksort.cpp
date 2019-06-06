/*******************************************************************\ 
|* Name: quicksort.cpp                                             *|
|* Author: crdrisko                                                *|
|* Date: 06/04/19-15:01:31                                         *|
|* Description: The Quicksort Algorithm                            *|
|*                                                                 *|
|*                                                                 *|
|* Complile Command: g++ quicksort.cpp -o quicksort.out -std=c++17 *|
\*******************************************************************/

#include <iostream>
#include <iomanip>
#include <vector>
#include <string>
#include <memory>
#include <string_view>

using Words = std::vector<std::shared_ptr<std::string>>;

void swap(Words& words, size_t first, size_t second);
void sort(Words& words);
void sort(Words& words, size_t start, size_t end);
void extract_words(Words& words, std::string_view text, std::string_view separators);
void show_words(const Words& words);
size_t max_word_length(const Words& words);

int main()
{
    Words words;
    std::string text;                                              // The string to be sorted
    const auto separators {" ,.!\"\n"};                            // Word delimiters

    // Read the string to be searched from the keyboard
    std::cout << " Enter a string terminated by *:" << std::endl;
    getline(std::cin, text, '*');
    extract_words(words, text, separators);
    if (words.empty())
    {
        std::cout << "No words in text." << std::endl;
        return 0;
    }
    sort(words);                                                   // Sort the words
    show_words(words);                                             // Output the words
}

void extract_words(Words& words, std::string_view text, std::string_view separators)
{
    size_t start {text.find_first_not_of(separators)};             // Start 1st word
    size_t end {};                                                 // Index for the end of a word

    while (start != std::string_view::npos)
    {
        end = text.find_first_of(separators, start + 1);           // Find end separator
        if (end == std::string_view::npos)                         // End of text?
            end = text.length();                                   // Yes, so set to last + 1
        words.push_back(std::make_shared<std::string>(text.substr(start, end - start)));
        start = text.find_first_not_of(separators, end + 1);       // Find next word
    }
}

void swap(Words& words, size_t first, size_t second)
{
    auto temp{words[first]};
    words[first] = words[second];
    words[second] = temp;
}

void sort(Words& words, size_t start, size_t end)
{
    // start index must be less than end index for 2 or more elements
    if (!(start < end))
        return;

    // Choose middle address to partition set
    swap(words, start, (start + end) / 2);                         // Swap middle address with start

    // Check words against chosen word
    size_t current {start};
    for (size_t i {start + 1}; i <= end; i++)
    {
        if (*words[i] < *words[start])                             // Is word less than chosen word?
            swap(words, ++current, i);                             // Yes, so swap to the left
    }

    swap(words, start, current);                                   // Swap chosen and last swapped words

    if (current > start) sort(words, start, current - 1);          // Sort left subset if exists
    if (end > current + 1) sort(words, current + 1, end);          // Sort right subset if exists
}

// Sort strings in ascending sequence
void sort(Words& words)
{
    if (!words.empty())
        sort(words, 0, words.size() - 1);
}

size_t max_word_length(const Words& words)
{
    size_t max{};
    for (auto& pword : words)
        if (max < pword->length()) max = pword->length();
    return max;
}

void show_words(const Words& words)
{
    const size_t field_width {max_word_length(words) + 1};
    const size_t words_per_line {8};
    std::cout << std::left << std::setw(field_width) << *words[0]; // Output the first word

    size_t words_in_line {};                                       // Words in current line
    for (size_t i {1}; i < words.size(); ++i)
    {   // Output newline when initial letter changes or after 8 per line
        if ((*words[i])[0] != (*words[i - 1])[0] || ++words_in_line == words_per_line)
        {
            words_in_line = 0;
            std::cout << std::endl;
        }
        std::cout << std::setw(field_width) << *words[i];          // Output a word
    }
    std::cout << std::endl;
}