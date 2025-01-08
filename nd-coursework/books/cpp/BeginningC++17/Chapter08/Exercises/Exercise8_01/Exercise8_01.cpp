// Copyright (c) 2019-2025 Cody R. Drisko. All rights reserved.
// Licensed under the MIT License. See the LICENSE file in the project root for more information.
//
// Name: Exercise8_01.cpp
// Author: crdrisko
// Date: 11/24/2020-06:19:58
// Description: Prompting a user for their birthday and validating the input

#include <iostream>
#include <string>
#include <vector>

int validate_input(int lower, int upper, const std::string& description);

int month();
int year();
int day(int month, int year);

int main()
{
    std::cout << "Please enter your date of birth." << std::endl;

    int m = month();
    int y = year();
    int d = day(m, y);

    std::vector<std::string> monthsOfTheYear {"January",
        "February",
        "March",
        "April",
        "May",
        "June",
        "July",
        "August",
        "September",
        "October",
        "November",
        "December"};

    std::cout << "Your date of birth is: " << monthsOfTheYear[m - 1] << " " << d << ", " << y << std::endl;
}

int validate_input(int lower, int upper, const std::string& description)
{
    int value;
    std::cout << "Enter a value between " << lower << " and " << upper << " which represents a valid " << description
              << ": ";
    std::cin >> value;

    while (value < lower || value > upper)
    {
        std::cout << "Invalid value entered. Please enter a " << description << " between " << lower << " and " << upper
                  << ": ";
        std::cin >> value;
    }

    return value;
}

int month()
{
    int month {validate_input(1, 12, "month")};

    return month;
}

int year()
{
    int year {validate_input(1867, 2020, "year")};

    return year;
}

int day(int month, int year)
{
    int upper_day {};

    switch (month)
    {
    case 1:
    case 3:
    case 5:
    case 7:
    case 8:
    case 10:
    case 12:
        upper_day = 31;
        break;
    case 2:
        if (year % 4 == 0)
            upper_day = 29;
        else
            upper_day = 28;
        break;
    case 4:
    case 6:
    case 9:
    case 11:
        upper_day = 30;
        break;
    }

    int day {validate_input(1, upper_day, "day")};

    return day;
}
