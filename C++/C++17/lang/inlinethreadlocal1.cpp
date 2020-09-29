// Copyright (c) 2017 by Nicolai Josuttis. All rights reserved.
// Licensed under the CCA-4.0 International License. See the LICENSE file in the project root for more information.
//
// Name: inlinethreadlocal1.cpp
// Author: crdrisko
// Date: 09/29/2020-07:06:38
// Description: Using the inline and thread_local variables in a translation unit that contains main()

#include <thread>

#include "inlinethreadlocal.hpp"

void foo();

int main()
{
    myThreadData.print("main() begin:");

    myThreadData.gName = "thread1 name";
    myThreadData.tName = "thread1 name";
    myThreadData.lName = "thread1 name";
    myThreadData.print("main() later:");

    std::thread t(foo);
    t.join();
    myThreadData.print("main() end:");
}
