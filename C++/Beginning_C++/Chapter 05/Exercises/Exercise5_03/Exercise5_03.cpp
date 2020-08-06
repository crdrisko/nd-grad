// Name: Exercise5_03.cpp - Version 1.0.0
// Author: cdrisko
// Date: 04/30/2020-13:37:08
// Description: Count the number of non-whitespace characters entered by a user

#include <iostream>

int main()
{
    std::size_t count {};
    char character {};
    std::cout << "Enter a sequence of characters terminated by '#': " << std::endl;

    do
    {
        std::cin >> character;
        ++count;
    } while (character != '#');

    std::cout << "You entered " << --count << " non-whitespace characters (not including '#')."
              << std::endl;
}
