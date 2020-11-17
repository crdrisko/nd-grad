// Name: Listing1_02.cpp
// Author: crdrisko
// Date: 11/13/2020-18:05:40
// Description: Using std::count to count newline characters

#include <algorithm>
#include <fstream>
#include <iterator>
#include <vector>

int count_lines(const std::string& filename)
{
    std::ifstream in(filename);

    return std::count(std::istreambuf_iterator<char>(in), std::istreambuf_iterator<char>(), '\n');
}

std::vector<int> count_lines_in_file(const std::vector<std::string>& files)
{
    std::vector<int> results;

    for (const auto& file : files)
        results.push_back(count_lines(file));

    return results;
}
