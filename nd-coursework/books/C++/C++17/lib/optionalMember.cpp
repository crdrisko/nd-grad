// Copyright (c) 2017 by Nicolai Josuttis. All rights reserved.
// Licensed under the CCA-4.0 International License. See the LICENSE file in the project root for more information.
//
// Name: optionalMember.cpp
// Author: crdrisko
// Date: 11/01/2020-12:35:46
// Description: Using std::optional<> when passing arguments and setting data members

#include <iostream>
#include <optional>
#include <string>

class Name
{
private:
    std::string first;
    std::optional<std::string> middle;
    std::string last;

public:
    Name(std::string f, std::optional<std::string> m, std::string l)
        : first {std::move(f)}, middle {std::move(m)}, last {std::move(l)}
    {
    }

    friend std::ostream& operator<<(std::ostream& strm, const Name& n)
    {
        strm << n.first << ' ';
        if (n.middle)
            strm << *n.middle << ' ';
        return strm << n.last;
    }
};

int main()
{
    Name n {"Jim", std::nullopt, "Knopf"};
    std::cout << n << '\n';

    Name m {"Donald", "Ervin", "Knuth"};
    std::cout << m << '\n';
}
