// Name: main.cpp
// Author: crdrisko
// Date: 08/26/2023-08:20:57
// Description:

#include <iostream>
#include <string>
#include <vector>

#include "Instruction.hpp"

int main() { setHealth(0, getHealth(0) + (getAgility(0) + getWisdom(0)) / 2); }
