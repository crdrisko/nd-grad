// Copyright (c) 2020 by Nicolai Josuttis. All rights reserved.
// Licensed under the CCA-4.0 International License. See the LICENSE file in the project root for more information.
//
// Name: stringmoveassign.cpp
// Author: crdrisko
// Date: 08/29/2021-08:56:25
// Description: Demonstrating how the capacity of std::string may change

#include <iostream>
#include <string>

int main()
{
    std::string s0;
    std::string s1 {"short"};
    std::string s2 {"a string with an extraordinarily long value"};
    std::cout << "- s0 capa: " << s0.capacity() << " ('" << s0 << "')\n";
    std::cout << "  s1 capa: " << s1.capacity() << " ('" << s1 << "')\n";
    std::cout << "  s2 capa: " << s2.capacity() << " ('" << s2 << "')\n";

    std::string s3 {std::move(s1)};
    std::string s4 {std::move(s2)};
    std::cout << "- s1 capa: " << s1.capacity() << " ('" << s1 << "')\n";
    std::cout << "  s2 capa: " << s2.capacity() << " ('" << s2 << "')\n";
    std::cout << "  s3 capa: " << s3.capacity() << " ('" << s3 << "')\n";
    std::cout << "  s4 capa: " << s4.capacity() << " ('" << s4 << "')\n";

    std::string s5 {"quite a reasonable value"};
    std::cout << "- s4 capa: " << s4.capacity() << " ('" << s4 << "')\n";
    std::cout << "  s5 capa: " << s5.capacity() << " ('" << s5 << "')\n";

    s4 = std::move(s5);
    std::cout << "- s4 capa: " << s4.capacity() << " ('" << s4 << "')\n";
    std::cout << "  s5 capa: " << s5.capacity() << " ('" << s5 << "')\n";
}
