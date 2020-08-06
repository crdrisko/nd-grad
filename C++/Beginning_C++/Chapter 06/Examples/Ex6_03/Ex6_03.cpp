// Name: Ex6_03.cpp - Version 1.0.0
// Author: cdrisko
// Date: 04/30/2020-21:57:28
// Description: Initializing pointers with strings

#include <iostream>

int main()
{
    const char* pstar1 {"Fatty Arbuckle"};
    const char* pstar2 {"Clara Bow"};
    const char* pstar3 {"Lassie"};
    const char* pstar4 {"Slim Pickens"};
    const char* pstar5 {"Boris Karloff"};
    const char* pstar6 {"Mae West"};
    const char* pstar7 {"Oliver Hardy"};
    const char* pstar8 {"Greta Garbo"};
    const char* pstr {"Your lucky star is "};

    std::cout << "Pick a lucky star! Enter a number between 1 and 8: ";
    std::size_t choice {};
    std::cin >> choice;

    switch (choice)
    {
    case 1: std::cout << pstr << pstar1 << std::endl; break;
    case 2: std::cout << pstr << pstar2 << std::endl; break;
    case 3: std::cout << pstr << pstar3 << std::endl; break;
    case 4: std::cout << pstr << pstar4 << std::endl; break;
    case 5: std::cout << pstr << pstar5 << std::endl; break;
    case 6: std::cout << pstr << pstar6 << std::endl; break;
    case 7: std::cout << pstr << pstar7 << std::endl; break;
    case 8: std::cout << pstr << pstar8 << std::endl; break;
    default: std::cout << "Sorry, you haven't got a lucky star." << std::endl;
    }
}
