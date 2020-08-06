// Name: Problem1-1.cpp - Version 1.0.0
// Author: cdrisko
// Date: 08/03/2020-11:56:14
// Description: Finding the largest size n of a problem that can be solved in a given amount of time

#include <cmath>
#include <functional>
#include <iomanip>
#include <iostream>
#include <string>
#include <vector>

void find_n(std::string fName, std::function<long double(long double)> f);
// int inv_n_lg_n(long double time);
// int inv_n_factorial(long double time);

int main()
{ 
    std::cout << std::setw(11) << "|" << std::setw(15) << std::left << "1 second" << std::right << '|'
                                      << std::setw(15) << std::left << "1 minute" << std::right << '|'
                                      << std::setw(15) << std::left << "1 hour" << std::right << '|'
                                      << std::setw(15) << std::left << "1 day" << std::right << '|'
                                      << std::setw(15) << std::left << "1 month" << std::right << '|'
                                      << std::setw(15) << std::left << "1 year" << std::right << '|'
                                      << std::setw(15) << std::left << "1 century"  << std::right << '|'
              << std::endl;

    std::string bar {};                             
    std::cout << bar.insert(0, 125, '-') << std::endl;


    find_n("lg(n)",   [](long double time) { return std::round( std::pow(2, time) ); });
    find_n("sqrt(n)", [](long double time) { return std::round( std::pow(time, 2) ); });
    find_n("n",       [](long double time) { return std::round( time); });
    // find_n("n lg(n)", [](long double time) { return std::round( inv_n_lg_n(time) ); });
    find_n("n^2",     [](long double time) { return std::round( std::sqrt(time) ); });
    find_n("n^3",     [](long double time) { return std::round( std::cbrt(time) ); });
    find_n("2^n",     [](long double time) { return std::round( std::log2(time) ); }); 
    // find_n("n!",      [](long double time) { return std::round( inv_n_factorial(time) ); });
}

void find_n(std::string fName, std::function<long double(long double)> f)
{
    std::vector<long double> times { 1, 60, 3600, 86400, 2.628e+6, 3.154e+7, 3.154e+9 };

    std::cout << std::setw(10) << std::left << fName << std::right << '|';

    for (const auto& time : times)
        std::cout << std::setw(15) << std::left << f(time * 1e6) << std::right << '|';

    std::cout << std::endl;
}
