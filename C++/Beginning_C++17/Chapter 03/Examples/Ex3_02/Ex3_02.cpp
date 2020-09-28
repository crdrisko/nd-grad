// Copyright (c) 2018 Ivor Horton and Peter Van Weert. Some rights reserved.
// Licensed under the Freeware License. See the LICENSE file in the project root for more information.
//
// Name: Ex3_02.cpp - Version 1.0.0
// Author: cdrisko
// Date: 04/23/2020-13:44:41
// Description: Operations with enumerations

#include <iomanip>
#include <iostream>

int main()
{
    enum class Day { Monday, Tuesday, Wednesday, Thursday, Friday, Saturday, Sunday };
    Day yesterday { Day::Monday }, today { Day::Tuesday }, tomorrow { Day::Wednesday };
    const Day poets_day { Day::Friday };

    enum class Punctuation : char { Comma = ',', Exclamation = '!', Question = '?' };
    Punctuation ch { Punctuation::Comma };

    std::cout << "yesterday's value is " << static_cast<int>(yesterday)
              << static_cast<char>(ch) << " but poets_day is " << static_cast<int>(poets_day)
              << static_cast<char>(Punctuation::Exclamation) << std::endl;

    today = Day::Thursday;                      // Assign new ...
    ch = Punctuation::Question;                 // ... enumerator values
    tomorrow = poets_day;                       // Copy enumerator value

    std::cout << "Is today's value(" << static_cast<int>(today)
              << ") the same as poets_day(" << static_cast<int>(poets_day)
              << ')' << static_cast<char>(ch) << std::endl;

    // ch = tomorrow;                           // Uncomment ...
    // tomorrow = Friday;                       // ... any of these ...
    // today = 6;                               // ... for an error.
}
