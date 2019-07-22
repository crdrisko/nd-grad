/***********************************************************************\ 
|* Name: Exercise3_2.cpp                                               *|
|* Author: crdrisko                                                    *|
|* Description: Calculates the number of square boxes that can fit on  *|
|*  a shelf without overhang.                                          *|
|*                                                                     *|
|*                                                                     *|
|* Complile Command: g++ Exercise3_2.cpp -o Exercise3_2.out -std=c++17 *|
\***********************************************************************/

#include <iostream>
#include <cmath>

int main()
{
    unsigned int box_side {};
    double shelf_length {}, shelf_depth {};

    std::cout << "Enter the box dimensions in inches: ";
    std::cin  >> box_side;
    std::cout << "Enter the length of the shelf in feet: ";
    std::cin  >> shelf_length; 
    std::cout << "Enter the depth of the shelf in feet: ";
    std::cin  >> shelf_depth;

    const unsigned inches_per_foot {12};
    long inches_length {}, inches_depth {};
 
    inches_length = static_cast<long>(shelf_length * inches_per_foot); 
    inches_depth  = static_cast<long>(shelf_depth  * inches_per_foot);
    
    long area_shelf {}, area_box {}, number_boxes {};

    area_shelf = inches_length * inches_depth;
    area_box = box_side * box_side;
    number_boxes = area_shelf / area_box; 

    std::cout << "The number of boxes that will fit on a " << inches_length << "x" 
              << inches_depth << " sq. in. shelf is " << number_boxes << " boxes."
              << std::endl;                          

}