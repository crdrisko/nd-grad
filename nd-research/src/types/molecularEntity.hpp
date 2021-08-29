// Copyright (c) 2019-2021 Cody R. Drisko. All rights reserved.
// Licensed under the MIT License. See the LICENSE file in the project root for more information.
//
// Name: molecularEntity.hpp
// Author: crdrisko
// Date: 07/28/2021-07:24:28
// Description:

#ifndef MOLECULARENTITY_HPP
#define MOLECULARENTITY_HPP

#include <memory>
#include <vector>

#include <common-utils/math.hpp>
#include <cpp-units/physicalQuantities.hpp>

using PositionVector = DryChem::Vector3D<CppUnits::Length>;
using VelocityVector = DryChem::Vector3D<CppUnits::Velocity>;

class MolecularEntity;
using MolecularEntityPtr = std::shared_ptr<MolecularEntity>;

struct DataStorage
{
    PositionVector positions;
    VelocityVector velocities;
};

class MolecularEntity
{
private:
    std::string name;
    CppUnits::Mass mass;
    std::size_t identifier;

protected:
    explicit MolecularEntity(const std::string& name_) : name {name_} {}

public:
    virtual ~MolecularEntity() = default;

    // Public functions...
    std::string getName() const { return name; }

    virtual CppUnits::Mass getMass() const            = 0;
    virtual PositionVector calculateCenterOfMass() = 0;

    virtual void add(MolecularEntityPtr&) {}
};

class CompositeMolecularEntity : public MolecularEntity
{
private:
    std::vector<MolecularEntityPtr> entities;

protected:
    explicit CompositeMolecularEntity(const std::string& name_) : MolecularEntity {name_} {}

public:
    // Public functions...
    CppUnits::Mass getMass() const override
    {
        CppUnits::Mass totalMass {};

        for (auto& entity : entities)
            totalMass += entity->getMass();

        return totalMass;
    }

    PositionVector calculateCenterOfMass() override
    {
        PositionVector totalCenterOfMass {};

        for (auto& entity : entities)
        {
            PositionVector centerOfMass = entity->calculateCenterOfMass();

            for (std::size_t i {}; i < totalCenterOfMass.size(); ++i)
                totalCenterOfMass[i] += (entity->getMass() * centerOfMass[i]) / getMass();
        }

        // for (auto& elem : totalCenterOfMass)
        //     elem /= getMass();

        return totalCenterOfMass;
    }

    void add(MolecularEntityPtr& entity) override { entities.push_back(entity); }
};

#endif
