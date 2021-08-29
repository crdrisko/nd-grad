// Copyright (c) 2017 by Nicolai Josuttis. All rights reserved.
// Licensed under the CCA-4.0 International License. See the LICENSE file in the project root for more information.
//
// Name: checkpath3.cpp
// Author: crdrisko
// Date: 01/06/2021-08:04:55
// Description: Switching over filesystem types using the std::filesystem::file_type enum

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

    namespace fs = std::filesystem;

    switch (fs::path p {argv[1]}; status(p).type())
    {
    case fs::file_type::not_found:
        std::cout << "path \"" << p.string() << "\" does not exist\n";
        break;
    case fs::file_type::regular:
        std::cout << '"' << p.string() << "\" exists with " << file_size(p) << " bytes\n";
        break;
    case fs::file_type::directory:
        std::cout << '"' << p.string() << "\" is a directory containing:\n";
        for (const auto& e : std::filesystem::directory_iterator {p})
            std::cout << " \"" << e.path().string() << "\"\n";
        break;
    default:
        std::cout << '"' << p.string() << "\" is a special file\n";
        break;
    }
}
