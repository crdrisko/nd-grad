// Copyright (c) 2017 by Nicolai Josuttis. All rights reserved.
// Licensed under the CCA-4.0 International License. See the LICENSE file in the project root for more information.
//
// Name: lambdathis.cpp
// Author: crdrisko
// Date: 09/29/2020-18:20:14
// Description: Capturing the this pointer within a lambda capture

#include <iostream>
#include <string>
#include <thread>

class Data
{
private:
    std::string name;

public:
    Data(const std::string& s) : name(s) {}

    auto startThreadWithCopyOfThis() const
    {
        // start and return new thread using this after 3 seconds
        using namespace std::literals;
        std::thread t([*this] {
                                std::this_thread::sleep_for(3s);
                                std::cout << name << '\n';
                              });
        return t;
    }
};

int main()
{
    std::thread t;
    {
        Data d {"c1"};
        t = d.startThreadWithCopyOfThis();
    }   // d is no longer valid
    t.join();
}
