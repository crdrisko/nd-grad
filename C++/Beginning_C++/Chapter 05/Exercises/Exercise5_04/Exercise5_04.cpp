// Name: Exercise5_04.cpp - Version 1.0.0
// Author: cdrisko
// Date: 04/30/2020-13:50:55
// Description: Reversing a C-style string using a for loop

#include <iostream>

int main()
{
    const size_t maxLength {1000};

    char cStyleString[maxLength] {};
    std::cout << "Enter a string of up to 1000 characters: ";
    std::cin.getline(cStyleString, maxLength);

    int count {};
    for (; count < maxLength && cStyleString[count] != '\0'; ++count) {}

    for (int i {count - 1}; i >= 0; --i)
        std::cout << cStyleString[i];

    std::cout << std::endl;
}
