// Copyright (c) 2020 by Nicolai Josuttis. All rights reserved.
// Licensed under the CCA-4.0 International License. See the LICENSE file in the project root for more information.
//
// Name: contmove.cpp
// Author: crdrisko
// Date: 08/17/2021-14:10:12
// Description: A program to check the difference between copying and moving an array and a vector of different elements types

#include <algorithm>
#include <array>
#include <chrono>
#include <cstdlib>   // for std::atoi()
#include <iostream>
#include <vector>

template<int numElems, typename T>
void test(int numLoops, const T& initialVal)
{
    // initialize durations:
    using millisecondsDouble = std::chrono::duration<double, std::milli>;
    millisecondsDouble arrCopy {0}, arrMove {0}, vecCopy {0}, vecMove {0};

    // declare source objects:
    std::array<T, numElems> arr;
    std::vector<T> vec;

    // loop several times over:
    for (int i = 0; i < numLoops; ++i)
    {
        // (re-)initialize source objects:
        std::fill(arr.begin(), arr.end(), initialVal);
        vec.resize(numElems);
        std::fill(vec.begin(), vec.end(), initialVal);

        // measure copy and move for arrays:
        auto t0 = std::chrono::steady_clock::now();
        auto arr1 {arr};   // copies all elements/values
        auto t1 = std::chrono::steady_clock::now();
        auto arr2 {std::move(arr)};   // moves all elements/values
        auto t2 = std::chrono::steady_clock::now();
        arrCopy += t1 - t0;
        arrMove += t2 - t1;

        // measure copy and move for vectors:
        auto t3 = std::chrono::steady_clock::now();
        auto vec1 {vec};   // copies all elements/values
        auto t4 = std::chrono::steady_clock::now();
        auto vec2 {std::move(vec)};   // moves elements/values as a whole
        auto t5 = std::chrono::steady_clock::now();
        vecCopy += t4 - t3;
        vecMove += t5 - t4;

        // disable warning about destinations never used:
        if (arr1[0] != arr2[0])
            std::cout << "oops" << '\n';
        if (vec1[0] != vec2[0])
            std::cout << "oops" << '\n';
    }

    // print measured durations:
    std::cout << " array copy: " << arrCopy.count() << '\n';
    std::cout << "       move: " << arrMove.count() << '\n';
    std::cout << "vector copy: " << vecCopy.count() << '\n';
    std::cout << "       move: " << vecMove.count() << '\n';
}

int main(int argc, char** argv)
{
    int numLoops = 1'000;
    if (argc > 1)
        numLoops = std::atoi(argv[1]);

    std::cout << "double:\n";
    test<10'000>(numLoops, 42.7);

    std::cout << "short string:\n";
    test<10'000>(numLoops, std::string {"short"});

    std::cout << "long string:\n";
    test<10'000>(numLoops, std::string {"a very long string to avoid small string optimization"});
}
