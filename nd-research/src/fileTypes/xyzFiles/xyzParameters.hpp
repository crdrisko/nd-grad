// Copyright (c) 2019-2020 Cody R. Drisko. All rights reserved.
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

#include <cpp-units/physicalQuantities.hpp>
#include <utils-api/containers.hpp>

namespace ND_Research
{
    template<typename T>
    using Matrix3D = Utilities_API::Containers::Vector3D<Utilities_API::Containers::Vector3D<T>>;


    struct XYZParameters
    {
        struct XYZFrameParameters
        {
            std::size_t numberOfAtoms {};
            PhysicalQuantities::Time runTime;
            Matrix3D<PhysicalQuantities::Length> Hmat;
        };

        struct XYZInferredParameters
        {
            std::size_t numberOfFrames {};
            PhysicalQuantities::Time timeStep;
        };

        std::vector<XYZFrameParameters> frame;
        XYZInferredParameters inferred;
    };

    using XYZParametersPtr = std::shared_ptr<XYZParameters>;
}

#endif
