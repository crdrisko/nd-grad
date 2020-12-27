// Copyright (c) 2019 by Anthony Williams. All rights reserved.
// Licensed under the Boost Software License. See the LICENSE file in the project root for more information.
//
// Name: Listing3_01.cpp
// Author: crdrisko
// Date: 12/27/2020-08:24:26
// Description: Protecting a list with a mutex

#include <algorithm>
#include <iostream>
#include <list>
#include <mutex>

std::list<int> some_list;
std::mutex some_mutex;

void add_to_list(int new_value)
{
    std::lock_guard<std::mutex> guard(some_mutex);
    some_list.push_back(new_value);
}

bool list_contains(int value_to_find)
{
    std::lock_guard<std::mutex> guard(some_mutex);
    return std::find(some_list.begin(), some_list.end(), value_to_find) != some_list.end();
}

int main()
{
    add_to_list(42);
    std::cout << "contains(1) = " << list_contains(1) << ", contains(42) = " << list_contains(42) << std::endl;
}
