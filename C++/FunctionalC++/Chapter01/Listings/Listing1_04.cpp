// Name: Listing1_04.cpp
// Author: crdrisko
// Date: 11/13/2020-18:11:57
// Description: Transformation using ranges

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
    return files | transform(count_lines);
}
