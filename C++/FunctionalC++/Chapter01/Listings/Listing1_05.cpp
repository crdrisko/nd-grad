// Name: Listing1_05.cpp
// Author: crdrisko
// Date: 11/13/2020-18:13:53
// Description: Transformation using ranges, modified

#include <vector>

std::vector<int> count_lines_in_file(const std::vector<std::string>& files)
{
    return files | transform(open_file)
                 | transform(count_lines);
}
