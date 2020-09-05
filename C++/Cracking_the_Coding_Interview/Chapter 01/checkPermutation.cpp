// Name: checkPermutation.cpp - Version 1.0.0
// Author: crdrisko
// Date: 08/27/2020-15:50:43
// Description:

#include <algorithm>
#include <iostream>
#include <string>

std::string sortString(std::string str);
bool checkPermutation(const std::string& str1, const std::string& str2);

int main()
{
    std::string str1 {"apple"};
    std::string str2 {"papel"};
    std::string str3 {"banana"};

    std::cout << std::boolalpha
              << "str1 + str1: " << checkPermutation(str1, str1) << '\n'
              << "str1 + str2: " << checkPermutation(str1, str2) << '\n'
              << "str1 + str3: " << checkPermutation(str1, str3) << '\n'
              << "str2 + str2: " << checkPermutation(str2, str2) << '\n'
              << "str2 + str3: " << checkPermutation(str2, str3) << '\n'
              << "str3 + str3: " << checkPermutation(str3, str3) << '\n';
}

std::string sortString(std::string str)
{
    std::sort(str.begin(), str.end());
    return str;
}

bool checkPermutation(const std::string& str1, const std::string& str2)
{
    if ( str1.length() != str2.length() )
        return false;

    return sortString(str1) == sortString(str2);
}
