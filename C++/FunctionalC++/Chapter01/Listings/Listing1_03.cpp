// Name: Listing1_03.cpp
// Author: crdrisko
// Date: 11/13/2020-18:10:00
// Description: Mapping files to line counts by using std::transform

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
    std::vector<int> results(files.size());

    std::transform(files.cbegin(), files.cend(), results.begin(), count_lines);

    return results;
}
