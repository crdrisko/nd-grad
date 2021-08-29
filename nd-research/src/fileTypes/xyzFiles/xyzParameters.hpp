// Copyright (c) 2019-2021 Cody R. Drisko. All rights reserved.
// Licensed under the MIT License. See the LICENSE file in the project root for more information.
//
// Name: xyzParameters.hpp - Version 1.0.0
// Author: crdrisko
// Date: 04/13/2020-08:09:47
// Description: Defines a few structures dedicated to holding the parameters associated with an .xyz file

#ifndef ND_RESEARCH_XYZPARAMETERS_HPP
#define ND_RESEARCH_XYZPARAMETERS_HPP

#include <cstddef>
#include <memory>
#include <vector>

#include <common-utils/math.hpp>
#include <cpp-units/physicalQuantities.hpp>

namespace ND_Research
{
    template<typename T>
    using Matrix3D = DryChem::Vector3D<DryChem::Vector3D<T>>;

    struct XYZParameters
    {
        struct XYZFrameParameters
        {
            std::size_t numberOfAtoms {};
            CppUnits::Time runTime {};
            Matrix3D<CppUnits::Length> Hmat {};
        };

        struct XYZInferredParameters
        {
            std::size_t numberOfFrames {1};
            CppUnits::Time timeStep {};
        };

        std::vector<XYZFrameParameters> frame;
        XYZInferredParameters inferred;
    };

    struct XYZData
    {
        std::string atomName;
        DryChem::Vector3D<CppUnits::Length> positions;
        DryChem::Vector3D<CppUnits::Velocity> velocities;
    };
}   // namespace ND_Research

#endif
