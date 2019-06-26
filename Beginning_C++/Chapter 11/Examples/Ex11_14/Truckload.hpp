// Name: Truckload.hpp
// Author: Cody R. Drisko (crdrisko)
// Date: 06/25/2019-10:01:13
// Description: For use with Ex11_14.cpp

#ifndef TRUCKLOAD_HPP
#define TRUCKLOAD_HPP
#include "Package.hpp"
#include <vector>

class Truckload
{
private:
    Package* pHead {};                                  // First in the list
    Package* pTail {};                                  // Last in the list
    Package* pCurrent {};                               // Last retrieved from the list

public:
    Truckload() = default;                              // Default constructor - empty truckload

    Truckload(SharedBox pBox)                           // Constructor - one Box
    { pHead = pTail = new Package{pBox}; }

    Truckload(const std::vector<SharedBox>& boxes);     // Constructor - vector of Boxes

    Truckload(const Truckload& src);                    // Copy constructor

    ~Truckload() { delete pHead; }                      // Destructor: clean up the list

    SharedBox getFirstBox();                            // Get the first Box
    SharedBox getNextBox();                             // Get the next Box
    void addBox(SharedBox pBox);                        // Add a new Box
    bool removeBox(SharedBox pBox);                     // Remove a Box from the Truckload
    void listBoxes() const;                             // Output the Boxes
};

#endif

