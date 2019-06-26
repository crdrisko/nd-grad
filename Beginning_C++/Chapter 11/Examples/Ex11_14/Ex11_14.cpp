// Name: Ex11_14.cpp
// Author: Cody R. Drisko (crdrisko) 
// Date: 06/25/2019-10:00:27
// Description: Using a linked list 

#include <cstdlib>                          // For random number generation
#include <ctime>                            // For the std::time() function
#include "Truckload.hpp"

// Function to generate a random integer between 1 and count
inline unsigned random(size_t count)
{
    return 1 + static_cast<unsigned>(std::rand() / (RAND_MAX / count + 1));
}

// Function to generate a Box with random dimensions
inline SharedBox randomBox()
{
    const size_t dimLimit {99};             // Upper limit on Box dimensions
    return std::make_shared<Box>(random(dimLimit), random(dimLimit), random(dimLimit));
}

int main()
{
    // Initialize the random number generator
    std::srand(static_cast<unsigned>(std::time(nullptr)));

    Truckload load1;                        // Create an empty list

    // Add 12 random Box objects to the list
    const size_t boxCount {12};
    for (size_t i {}; i < boxCount; ++i)
        load1.addBox(randomBox());
    
    std::cout << "The first list:\n";
    load1.listBoxes();

    // Copy the truckload
    Truckload copy {load1};
    std::cout << "\nThe copied truckload:\n";
    copy.listBoxes();

    // Find the largest Box in the list
    SharedBox largestBox {load1.getFirstBox()};

    SharedBox nextBox {load1.getNextBox()};
    while (nextBox)
    {
        if (nextBox->compare(*largestBox) > 0)
            largestBox = nextBox;
        nextBox = load1.getNextBox();
    }

    std::cout << std::endl;
    std::cout << "\nThe largest Box in the first list is:";
    largestBox->listBox();
    std::cout << std::endl;
    load1.removeBox(largestBox);
    std::cout << "\nAfter deleting the largest box, the list contains:\n";
    load1.listBoxes();

    const size_t nBoxes {20};               // Number of vector elements
    std::vector<SharedBox> boxes;           // Array of Box objects

    for (size_t i {}; i < nBoxes; ++i)
        boxes.push_back(randomBox());

    Truckload load2 {boxes};
    std::cout << std::endl;
    std::cout << "\nThe second list:\n";
    load2.listBoxes();

    auto smallestBox = load2.getFirstBox();
    for (auto nextBox = load2.getNextBox(); nextBox; nextBox = load2.getNextBox())
        if (nextBox->compare(*smallestBox) < 0)
            smallestBox = nextBox;

    std::cout << "\nThe smallest Box in the second list is:";
    smallestBox->listBox();
    std::cout << std::endl; 
}
