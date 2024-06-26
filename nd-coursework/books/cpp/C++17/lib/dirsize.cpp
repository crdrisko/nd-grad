// Copyright (c) 2017 by Nicolai Josuttis. All rights reserved.
// Licensed under the CCA-4.0 International License. See the LICENSE file in the project root for more information.
//
// Name: dirsize.cpp
// Author: crdrisko
// Date: 11/17/2020-06:30:19
// Description: Another example of running std::transform_reduce in parallel

#include <cstdlib>      // for EXIT_FAILURE
#include <execution>    // for the execution policy
#include <filesystem>   // filesystem library
#include <functional>
#include <iostream>
#include <numeric>   // for std::transform_reduce()
#include <vector>

int main(int argc, char* argv[])
{
    // root directory is passed as command line argument:
    if (argc < 2)
    {
        std::cout << "Usage: " << argv[0] << " <path> \n";
        return EXIT_FAILURE;
    }

    std::filesystem::path root {argv[1]};

    // init list of all file paths in passed file tree:
    std::vector<std::filesystem::path> paths;

    try
    {
        std::filesystem::recursive_directory_iterator dirpos {root};
        std::copy(begin(dirpos), end(dirpos), std::back_inserter(paths));
    }
    catch (const std::exception& e)
    {
        std::cerr << "EXCEPTION: " << e.what() << std::endl;
        return EXIT_FAILURE;
    }

    // accumulate size of all regular files:
    auto sz = std::transform_reduce(/* std::execution::par,                 // parallel execution */
        paths.cbegin(),
        paths.cend(),                          // range
        std::uintmax_t {0},                    // initial value
        std::plus<>(),                         // accumulate...
        [](const std::filesystem::path& p) {   // file size if regular file
            return is_regular_file(p) ? file_size(p) : std::uintmax_t {0};
        });

    std::cout << "size of all " << paths.size() << " regular files: " << sz << '\n';
}
