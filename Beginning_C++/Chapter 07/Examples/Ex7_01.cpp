/*************************************************************\ 
|* Name: Ex7_01.cpp                                          *|
|* Author: crdrisko                                          *|
|* Description: Concatenating strings                        *|
|*                                                           *|
|*                                                           *|
|* Complile Command: g++ Ex7_01.cpp -o Ex7_01.out -std=c++17 *|
\*************************************************************/

#include <iostream>
#include <string>

int main()
{
    std::string first;                              // Stores the first name
    std::string second;                             // Stores the second name

    std::cout << "Enter your first name: ";
    std::cin  >> first;                             // Read first name

    std::cout << "Enter your second name: ";
    std::cin  >> second;                            // Read second name

    std::string sentence {"Your full name is "};    // Create basic sentence
    sentence += first + " " + second + ".";         // Augment with names

    std::cout << sentence << std::endl;             // Output the sentence
    std::cout << "The sting contains "              // Output its length
              << sentence.length() << " characters." << std::endl;
}