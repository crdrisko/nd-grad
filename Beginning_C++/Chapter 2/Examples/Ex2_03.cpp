/*************************************************************\ 
|* Name: Ex2_03.cpp                                          *|
|* Author: crdrisko                                          *|
|* Description: Sizing a pond for happy fish                 *|
|*                                                           *|
|*                                                           *|
|* Complile Command: g++ Ex2_03.cpp -o Ex2_03.out -std=c++17 *|
\*************************************************************/

#include <iostream>
#include <cmath>
#include <iomanip>

int main()
{
    // 2 square feet pond surface for every 6  inches of fish
    const double fish_factor {2.0/0.5};     // Area per unit length of fish
    const double inches_per_foot {12.0};    
    const double pi {3.141592653589793238};  
                                            
    double fish_count {};                   // Number of fish
    double fish_length {};                  // Average length of fish
                                            
    std::cout << "Enter the number of fish you want to keep: ";
    std::cin  >> fish_count;                
    std::cout << "Enter the average fish length in inches: ";
    std::cin  >> fish_length;                
    fish_length /= inches_per_foot;         // Convert to feet

    // Calculate the required surface area
    const double pond_area {fish_count * fish_length * fish_factor};

    // Calculate the pond diameter from the area
    const double pond_diameter {2.0 * std::sqrt(pond_area/pi)};

    std::cout << "\nPond diameter required for " << fish_count << " fish is "
              << std::scientific << std::setprecision(2)       
              << pond_diameter << " feet.\n";
}