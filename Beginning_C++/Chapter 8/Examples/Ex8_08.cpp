/*************************************************************\ 
|* Name: Ex8_08.cpp                                          *|
|* Author: crdrisko                                          *|
|* Date: 05/21/19-13:20:41                                   *|
|* Description: Using a reference parameter                  *|
|*                                                           *|
|*                                                           *|
|* Complile Command: g++ Ex8_08.cpp -o Ex8_08.out -std=c++17 *|
\*************************************************************/

#include <iostream>
#include <iomanip>
#include <vector>
#include <string>

using std::string;
using std::vector;

void find_words(vector<string>& words, const string& str, const string& separators);
void list_words(const vector<string>& words);

int main()
{
    string text;                                                // The string to be searched
    std::cout << "Enter some text terminated by *:\n";
    std::getline(std::cin, text, '*');

    const string separators {" ,;:.\"!?'\n"};                   // Word delimiters
    vector<string> words;                                       // Words found

    find_words(words, text, separators);
    list_words(words);
}

void find_words(vector<string>& words, const string& str, const string& separators)
{
    size_t start {str.find_first_not_of(separators)};           // Find word start index
    size_t end {};                                              // Index for the end of a word

    while (start != string::npos)
    {
        end = str.find_first_of(separators, start + 1);     // Find end of word
        if (end == string::npos)                                // Found a separator?
            end = str.length();                                 // No, so set to last + 1
        
        words.push_back(str.substr(start, end - start));        // Store the word
        start = str.find_first_not_of(separators, end + 1);     // Find 1st character of the next word
    }
}

void list_words(const vector<string>& words)
{
    std::cout << "Your string contains the following " << words.size() << " words:\n";
    size_t count {};                                            // Number output
    for (const auto& word : words)
    {
        std::cout << std::setw(15) << word;
        if (!(++count % 5))
            std::cout << std::endl;
    }
    std::cout << std::endl;
}