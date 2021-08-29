// Copyright (c) 2020 by Nicolai Josuttis. All rights reserved.
// Licensed under the CCA-4.0 International License. See the LICENSE file in the project root for more information.
//
// Name: thread.cpp
// Author: crdrisko
// Date: 08/29/2021-08:55:31
// Description: Demonstrating the use of move semantics with multithreading applications using std::thread and std::jthread

#include <iostream>
#include <thread>
#include <vector>

void doThis(const std::string& arg) { std::cout << "doThis(): " << arg << '\n'; }
void doThat(const std::string& arg) { std::cout << "doThat(): " << arg << '\n'; }

int main()
{
    std::vector<std::thread> threads;   // better std::jthread since C++20

    // start a couple of threads:
    std::string someArg {"Black Lives Matter"};
    threads.push_back(std::thread {doThis, someArg});
    threads.push_back(std::thread {doThat, std::move(someArg)});

    // ...

    // wait for all threads to end:
    for (auto& t : threads)
        t.join();
}
