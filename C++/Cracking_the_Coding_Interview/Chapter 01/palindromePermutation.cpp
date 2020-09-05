// Name: palindromePermutation.cpp - Version 1.0.0
// Author: crdrisko
// Date: 08/28/2020-11:11:53
// Description:

#include <cctype>
#include <cstddef>
#include <iostream>
#include <map>
#include <string_view>

constexpr bool isEven(int i);
constexpr bool isOdd(int i);
bool palindromePermutation(std::string_view str);


int main()
{
    std::string str1 {"racecar"};
    std::string str2 {"carcare"};
    std::string str3 {"carlcare"};
    std::string str4 {"abba"};
    std::string str5 {"bbaa"};
    std::string str6 {"banana"};
    std::string str7 {"Tact Coa"};
    std::string str8 {"acto cta"};

    std::cout << std::boolalpha
              << "str1: " << palindromePermutation(str1) << '\n'
              << "str2: " << palindromePermutation(str2) << '\n'
              << "str3: " << palindromePermutation(str3) << '\n'
              << "str4: " << palindromePermutation(str4) << '\n'
              << "str5: " << palindromePermutation(str5) << '\n'
              << "str6: " << palindromePermutation(str6) << '\n'
              << "str7: " << palindromePermutation(str7) << '\n'
              << "str8: " << palindromePermutation(str8) << '\n';
}

constexpr bool isEven(int i)
{
    return (i % 2) == 0;
}

constexpr bool isOdd(int i)
{
    return ((i + 1) % 2) == 0;
}

bool palindromePermutation(std::string_view str)
{
    std::map<char, std::size_t> charCounts;
    std::size_t size {};

    for (const auto& ch : str)
    {
        if ( !std::isalpha(ch) )
            continue;

        ++charCounts[std::tolower(ch)];
        ++size;
    }

    if ( isEven(size) )
    {
        for (const auto& [ch, count] : charCounts)
            if ( isOdd(count) )
                return false;
    }
    else
    {
        std::size_t oddCounts {};

        for (const auto& [ch, count] : charCounts)
            if ( isOdd(count) )
                ++oddCounts;

        if (oddCounts != 1)
            return false;
    }

    return true;
}
