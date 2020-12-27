// Copyright (c) 2017 by Nicolai Josuttis. All rights reserved.
// Licensed under the CCA-4.0 International License. See the LICENSE file in the project root for more information.
//
// Name: checkpath1.cpp
// Author: crdrisko
// Date: 12/22/2020-07:46:10
// Description: Demonstrating the use of some of the main parts of the std::filesystem

#include <cstdlib>                                          // for EXIT_FAILURE
#include <filesystem>
#include <iostream>

int main(int argc, char* argv[])
{
    if (argc < 2)
    {
        std::cout << "Usage: " << argv[0] << " <path> \n";
        return EXIT_FAILURE;
    }

    std::filesystem::path p {argv[1]};                      // p represents a filesystem path (might not exist)

    if (is_regular_file(p))                                 // is path p a regular file?
    {
        std::cout << p << " exists with " << file_size(p) << " bytes\n";
    }
    else if (is_directory(p))                               // is path a directory?
    {
        std::cout << p << " is a directory containing:\n";

        for (const auto& e : std::filesystem::directory_iterator {p})
            std::cout << " " << e.path() << '\n';
    }
    else if (exists(p))                                     // does path p actually exist?
    {
        std::cout << p << " is a special file\n";
    }
    else
    {
        std::cout << "path " << p << " does not exist\n";
    }
}
