// Name: Listing1_01.cpp
// Author: crdrisko
// Date: 11/13/2020-17:58:55
// Description: Calculating the number of lines the imperative way

#include <fstream>
#include <vector>

std::vector<int> count_lines_in_file(const std::vector<std::string>& files)
{
    std::vector<int> results;
    char c = 0;

    for (const auto& file : files)
    {
        int line_count = 0;

        std::ifstream in(file);

        while (in.get(c))
            if (c == '\n')
                line_count++;

        results.push_back(line_count);
    }

    return results;
}
