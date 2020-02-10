// Name: array.hpp - Version 1.0.0
// Author: Cody R. Drisko (crdrisko)
// Date: 12/16/2019-13:28:44
// Description:

#ifndef ARRAY_HPP
#define ARRAY_HPP

#include <stdexcept>                            // For standard exception types
#include <string>                               // For std::to_string()
#include <utility>                              // For std::as_const()

template <typename T>
class Array
{
private:
    T* elements;                                // Array of type T
    size_t size;                                // Number of array elements

public:
    explicit Array(size_t arraySize);           // Constructor
    Array(const Array& array);                  // Copy constructor
    ~Array();                                   // Destructor
    T& operator[](size_t index);                // Subscript operator
    const T& operator[](size_t index) const;    // Subscript operator-const arrays
    Array& operator=(const Array& rhs);         // Assignment operator
    size_t getSize() const { return size; }     // Accessor for size    
};

// Constructor
template <typename T>                           // This is a template with parameter T
Array<T>::Array(size_t arraySize) : elements {new T[arraySize]}, size {arraySize}
{}

// Copy constructor
template <typename T>
Array<T>::Array(const Array& array) : Array{array.size}
{
    for (size_t i {}; i < size; ++i)
        elements[i] = array.elements[i];
}

// Destructor
template <typename T>
Array<T>::~Array()
{
    delete[] elements;
}

// Const substript operator
template <typename T>
const T& Array<T>::operator[](size_t index) const
{
    if (index >= size)
        throw std::out_of_range {"Index too large: " + std::to_string(index)};
    
    return elements[index];
}

// Non-const subscript operator in terms of const one
template <typename T>
T& Array<T>::operator[](size_t index)
{
    // Using the "Const-and-back-again" idoiom 
    return const_cast<T&>(std::as_const(*this)[index]);
}

// Copy assignment operator in terms of the copy constructor
template <typename T>
Array<T>& Array<T>::operator=(const Array& rhs)
{
    if (&rhs != this)               // If lhs != rhs...
    {                               // ...do the assignment...
        delete[] elements;          // Release any free store memory

        size = rhs.size;            // Copy the members of rhs into lhs
        elements = new T[size];
        for (size_t i {}; i < size; ++i)
            elements[i] = rhs.elements[i];
    }
    return *this;                   // ...return lhs
}

#endif
