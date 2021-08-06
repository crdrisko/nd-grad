// Copyright (c) 2020 by Nicolai Josuttis. All rights reserved.
// Licensed under the CCA-4.0 International License. See the LICENSE file in the project root for more information.
//
// Name: initperf.cpp
// Author: crdrisko
// Date: 08/05/2021-07:56:53
// Description: A full program for comparing the different approaches to initializing members with move semantics

#include <chrono>
#include <cstdlib>   // for std::atoi()
#include <iostream>
#include <map>
#include <string>

//*************************************************
// the 3 approaches to initialize a Person
//*************************************************

namespace classic
{
    class Person
    {
    private:
        std::string first;   // first name
        std::string last;    // last name

    public:
        Person(const std::string& f, const std::string& l) : first {f}, last {l} {}

        // ...
    };
}   // namespace classic

namespace all
{
    class Person
    {
    private:
        std::string first;   // first name
        std::string last;    // last name

    public:
        Person(const std::string& f, const std::string& l) : first {f}, last {l} {}

        Person(const std::string& f, std::string&& l) : first {f}, last {std::move(l)} {}

        Person(std::string&& f, const std::string& l) : first {std::move(f)}, last {l} {}

        Person(std::string&& f, std::string&& l) : first {std::move(f)}, last {std::move(l)} {}

        Person(const char* f, const char* l) : first {f}, last {l} {}

        Person(const char* f, const std::string& l) : first {f}, last {l} {}

        Person(const char* f, std::string&& l) : first {f}, last {std::move(l)} {}

        Person(const std::string& f, const char* l) : first {f}, last {l} {}

        Person(std::string&& f, const char* l) : first {std::move(f)}, last {l} {}

        // ...
    };
}   // namespace all

namespace valmove
{
    class Person
    {
    private:
        std::string first;   // first name
        std::string last;    // last name

    public:
        Person(std::string f, std::string l) : first {std::move(f)}, last {std::move(l)} {}

        // ...
    };
}   // namespace valmove

//*************************************************
// measure functions (with long strings and SSO)
//*************************************************

// measure num initializations of whatever is currently defined as Person:
template<typename PersonT>
std::chrono::nanoseconds measure(int num)
{
    std::chrono::nanoseconds totalDur {0};

    for (int i = 0; i < num; ++i)
    {
        std::string fname = "a firstname a bit too long for SSO";
        std::string lname = "a lastname a bit too long for SSO";

        // measure how long it takes to create 3 Persons in different ways:
        auto t0 = std::chrono::steady_clock::now();
        PersonT p1 {"a firstname too long for SSO", "a lastname too long for SSO"};
        PersonT p2 {fname, lname};
        PersonT p3 {std::move(fname), std::move(lname)};
        auto t1 = std::chrono::steady_clock::now();

        totalDur += t1 - t0;
    }

    return totalDur;
}

// same using short strings so that strings don't allocate memory:
template<typename PersonT>
std::chrono::nanoseconds measureSSO(int num)
{
    std::chrono::nanoseconds totalDur {0};

    for (int i = 0; i < num; ++i)
    {
        std::string fname = "short first";
        std::string lname = "short last";

        // measure how long it takes to create 3 Persons in different ways:
        auto t0 = std::chrono::steady_clock::now();
        PersonT p1 {"a firstname", "a lastname"};
        PersonT p2 {fname, lname};
        PersonT p3 {std::move(fname), std::move(lname)};
        auto t1 = std::chrono::steady_clock::now();

        totalDur += t1 - t0;
    }

    return totalDur;
}

//*************************************************
// main()
//*************************************************

int main(int argc, const char** argv)
{
    int num = 1000;

    if (argc > 1)
        num = std::atoi(argv[1]);

    // a few iterations to make the CPU hot:
    measure<classic::Person>(num / 10);
    measureSSO<all::Person>(num / 10);

    std::map<std::string, std::chrono::duration<double, std::milli>> data;
    int numLoops = 10;

    for (int i = 0; i < numLoops; ++i)
    {
        // measure:
        data["a: classic:      "] += measure<classic::Person>(num / numLoops);
        data["b: all:          "] += measure<all::Person>(num / numLoops);
        data["c: valmove:      "] += measure<valmove::Person>(num / numLoops);
        data["d: classicSSO:   "] += measureSSO<classic::Person>(num / numLoops);
        data["e: allSSO:       "] += measureSSO<all::Person>(num / numLoops);
        data["f: valmoveSSO:   "] += measureSSO<valmove::Person>(num / numLoops);
    }

    for (const auto& d : data)
        std::cout << "  " << d.first << d.second.count() / numLoops << "ms\n";
}
