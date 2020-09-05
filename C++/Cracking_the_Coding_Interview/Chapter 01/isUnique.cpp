// Name: isUnique.cpp - Version 1.0.0
// Author: crdrisko
// Date: 08/27/2020-09:07:31
// Description:

#include <cstddef>
#include <iostream>
#include <string>
#include <string_view>
#include <vector>

bool isUnique_brute(std::string_view str);
bool isUnique_vector(std::string_view str);

int main()
{
    std::string str1 {"apple"};
    std::string str2 {"banana"};
    std::string str3 {"orange"};
    std::string str4 {"lemon"};

    std::cout << std::boolalpha << "      Brute\tVector\n" 
              << "str1: " << isUnique_brute(str1) << '\t' << isUnique_vector(str1) << '\n'
              << "str2: " << isUnique_brute(str2) << '\t' << isUnique_vector(str2) << '\n'
              << "str3: " << isUnique_brute(str3) << '\t' << isUnique_vector(str3) << '\n'
              << "str4: " << isUnique_brute(str4) << '\t' << isUnique_vector(str4) << '\n';
}

// Brute force - O(n^2)
bool isUnique_brute(std::string_view str)
{
    for (std::size_t i {}; i < str.size() - 1; ++i)
    {
        for (std::size_t j {i + 1}; j < str.size(); ++j)
        {
            if (str[i] == str[j])
                return false;
        }
    }

    return true;
}

// With vector of booleans - O(n)
bool isUnique_vector(std::string_view str)
{
    std::vector<bool> vec(128, false);

    for (std::size_t i {}; i < str.size(); ++i)
    {
        int val {str[i]};

        if (vec[val])
            return false;
        
        vec[val] = true;
    }

    return true;
}

