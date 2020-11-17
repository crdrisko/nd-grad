// Name: main.cpp
// Author: crdrisko
// Date: 11/17/2020-11:23:59
// Description: Mapping files to line counts by using std::transform

#include <algorithm>
#include <fstream>
#include <iostream>
#include <iterator>
#include <string>
#include <unordered_map>
#include <vector>

/**
 * This function opens a file specified by the filename argument,
 * and counts the number of lines in said file
 */
int count_lines(const std::string& filename)
{
    std::ifstream in(filename);
    in.unsetf(std::ios_base::skipws);

    // We are creating an iterator over the input stream and
    // passing it to the count algorithm to count the number
    // of newline characters
    return std::count(std::istream_iterator<char>(in),
                      std::istream_iterator<char>(),
                      '\n');
}

/**
 * Given a list of files, this function returns a list of
 * line counts for each of them
 */
std::vector<int> count_lines_in_files(const std::vector<std::string>& files)
{
    // Since we know the size of the resulting vector, we can
    // preallocate the needed number of elememnts
    std::vector<int> results(files.size());

    // Instead of using the raw for loop like in the count-lines-stdcount
    // example, we are using the std::transform algorithm to
    // convert the list of file names into a list of line counts
    std::transform(files.cbegin(), files.cend(), results.begin(), count_lines);

    return results;
}

int main(int argc, char* argv[])
{
    auto results = count_lines_in_files({"main.cpp", "Makefile"});

    for (auto result : results)
        std::cout << result << " line(s)\n";

    return 0;
}
