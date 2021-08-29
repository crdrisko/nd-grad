// Copyright (c) 2019-2021 Cody R. Drisko. All rights reserved.
// Licensed under the MIT License. See the LICENSE file in the project root for more information.
//
// Name: md.cpp
// Author: crdrisko
// Date: 07/30/2021-07:21:12
// Description:

#include <fstream>
#include <iostream>
#include <random>
#include <vector>

#include <common-utils/math.hpp>
#include <cpp-units/physicalQuantities.hpp>

using namespace CppUnits;

int main()
{
    // Main parameters of a standard (basic) MD simulation
    Time runTime {};
    Time timeStep {};

    Temperature desiredTemperature {};
    DryChem::Vector3D<Length> boxDimensions {};

    int seed {};

    // Files:
    std::ifstream inputFile;
    std::ofstream outputFile;

    std::ofstream trajectoryFile;
    std::ofstream statisticsFile;


    // 1) Parse input file

    // 2) Initialize velocities
    std::mt19937 gen {seed};

    std::normal_distribution velDist;

    double t = velDist(gen);

    //
}
