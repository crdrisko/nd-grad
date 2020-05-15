// Copyright (c) 2020 Cody R. Drisko. All rights reserved.
// Licensed under the MIT License. See the LICENSE file in the project root for license information.
//
// Name: testDataFieldParsing.cpp - Version 1.0.0
// Author: cdrisko
// Date: 05/14/2020-08:06:45
// Description: Provides ~100% unit test coverage over all data field parsing utilities in the repository

#include <cstddef>
#include <limits>
#include <memory>
#include <string>
#include <string_view>
#include <vector>

#include <gtest/gtest.h>
#include <utils-api/files.hpp>

#include "../testAssertions.hpp"
#include "../../src/utilities/dataFields.hpp"
#include "../../src/utilities/dataFieldParser.hpp"
#include "../../src/fileTypes/rnemdFiles/rnemdParameters.hpp"

using namespace ND_Research;

int main(int argc, char** argv)
{
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}

GTEST_TEST(testDataFieldParsing, individualLabelsAreFoundAtTheCorrectLocationsInTheFullLabel)
{
    std::vector<std::string> outputTypes {"Cl-", "Na+", "SPCE_RB_0"};
    std::string_view sampleLabel {"#	z(Angstroms)	Temperature(K)	Velocity(angstroms/fs)			Density(g cm^-3)	Activity(unitless)(Cl-	Na+	)		Electric Field(kcal/mol/angstroms/e)			Electrostatic Potential(kcal/mol/e)"};

    DataFieldPtr rnemdAxis         { std::make_shared<DataField>("z(Angstroms)") };
    DataFieldPtr temperature       { std::make_shared<DataField>("Temperature(K)") };
    DataFieldPtr velocity          { std::make_shared<DataFieldArray>("Velocity(angstroms/fs)") };
    DataFieldPtr angularVelocity   { std::make_shared<DataFieldArray>("AngularVelocity(angstroms^2/fs)") };
    DataFieldPtr density           { std::make_shared<DataField>("Density(g cm^-3)") };
    DataFieldPtr activity          { std::make_shared<DataFieldVector>("Activity(unitless)", outputTypes) };
    DataFieldPtr electricField     { std::make_shared<DataFieldArray>("Electric Field(kcal/mol/angstroms/e)") };
    DataFieldPtr electricPotential { std::make_shared<DataField>("Electrostatic Potential(kcal/mol/e)") };

    rnemdAxis->findLabelStartLocation(sampleLabel);
    temperature->findLabelStartLocation(sampleLabel);
    velocity->findLabelStartLocation(sampleLabel);
    angularVelocity->findLabelStartLocation(sampleLabel);
    density->findLabelStartLocation(sampleLabel);
    activity->findLabelStartLocation(sampleLabel);
    electricField->findLabelStartLocation(sampleLabel);
    electricPotential->findLabelStartLocation(sampleLabel);

    assertThat(rnemdAxis->getLabelStartIndex()).hasAValueOf(2);
    assertThat(temperature->getLabelStartIndex()).hasAValueOf(15);
    assertThat(velocity->getLabelStartIndex()).hasAValueOf(30);
    assertThat(angularVelocity->getLabelStartIndex()).hasAValueOf(std::numeric_limits<unsigned int>::max());
    assertThat(density->getLabelStartIndex()).hasAValueOf(55);
    assertThat(activity->getLabelStartIndex()).hasAValueOf(72);
    assertThat(electricField->getLabelStartIndex()).hasAValueOf(102);
    assertThat(electricPotential->getLabelStartIndex()).hasAValueOf(141);
}

GTEST_TEST(testDataFieldParsing, dataFieldsCanBeParsedIndividuallyButRequiresTooMuchInformationAtCompileTime)
{
    Utilities_API::Files::TextFile actualFile {"../../samples/rnemd/double.rnemd"};
    std::vector< std::vector<std::string> > actualData {actualFile.getSuperDataVector()};

    std::vector<std::string> outputTypes {"Cl-", "Na+", "SPCE_RB_0"};
    std::string_view sampleLabel {"#	z(Angstroms)	Temperature(K)	Velocity(angstroms/fs)			Density(g cm^-3)	Activity(unitless)(Cl-	Na+	)		Electric Field(kcal/mol/angstroms/e)			Electrostatic Potential(kcal/mol/e)"};

    DataFieldPtr rnemdAxis         { std::make_shared<DataField>("z(Angstroms)") };
    DataFieldPtr temperature       { std::make_shared<DataField>("Temperature(K)") };
    DataFieldPtr velocity          { std::make_shared<DataFieldArray>("Velocity(angstroms/fs)") };
    DataFieldPtr angularVelocity   { std::make_shared<DataFieldArray>("AngularVelocity(angstroms^2/fs)") };
    DataFieldPtr density           { std::make_shared<DataField>("Density(g cm^-3)") };
    DataFieldPtr activity          { std::make_shared<DataFieldVector>("Activity(unitless)", outputTypes) };
    DataFieldPtr electricField     { std::make_shared<DataFieldArray>("Electric Field(kcal/mol/angstroms/e)") };
    DataFieldPtr electricPotential { std::make_shared<DataField>("Electrostatic Potential(kcal/mol/e)") };

    rnemdAxis->findLabelStartLocation(sampleLabel);
    temperature->findLabelStartLocation(sampleLabel);
    velocity->findLabelStartLocation(sampleLabel);
    density->findLabelStartLocation(sampleLabel);
    activity->findLabelStartLocation(sampleLabel);
    electricField->findLabelStartLocation(sampleLabel);
    electricPotential->findLabelStartLocation(sampleLabel);

    for (const auto& row : actualData)
    {
        unsigned int dataStartIndex {};

        rnemdAxis->processData(row, dataStartIndex);
        temperature->processData(row, dataStartIndex);
        velocity->processData(row, dataStartIndex);
        density->processData(row, dataStartIndex);
        activity->processData(row, dataStartIndex);
        electricField->processData(row, dataStartIndex);
        electricPotential->processData(row, dataStartIndex);
    }


    RNEMDDataPtr rnemdData { std::make_shared<RNEMDData>() };

    rnemdAxis->convertToPhysicalQuantity(rnemdData->rnemdAxis);
    temperature->convertToPhysicalQuantity(rnemdData->temperature);
    dynamic_cast<DataFieldArray*>( velocity.get() )->convertToPhysicalQuantity(rnemdData->velocity);
    dynamic_cast<DataFieldArray*>( angularVelocity.get() )->convertToPhysicalQuantity(rnemdData->angularVelocity);
    density->convertToPhysicalQuantity(rnemdData->density);
    dynamic_cast<DataFieldVector*>( activity.get() )->convertToPhysicalQuantity(rnemdData->activity);
    dynamic_cast<DataFieldArray*>( electricField.get() )->convertToPhysicalQuantity(rnemdData->electricField);
    electricPotential->convertToPhysicalQuantity(rnemdData->electricPotential);

    for (std::size_t i {}; i < actualData[0].size(); ++i)
    {
        assertThat(rnemdData->rnemdAxis[i].getMagnitude()).hasAValueNear( std::stold(actualData[i][0]) );
        assertThat(rnemdData->temperature[i].getMagnitude()).hasAValueNear( std::stold(actualData[i][1]) );
        assertThat(rnemdData->density[i].getMagnitude()).hasAValueNear( std::stold(actualData[i][5]) );
        assertThat(rnemdData->activity[0][i].getMagnitude()).hasAValueNear( std::stold(actualData[i][6]) );
        assertThat(rnemdData->activity[1][i].getMagnitude()).hasAValueNear( std::stold(actualData[i][7]) );
        assertThat(rnemdData->electricPotential[i].getMagnitude()).hasAValueNear( std::stold(actualData[i][11]) );

        for (std::size_t j {}; j < 3; ++j)
        {
            assertThat(rnemdData->velocity[j][i].getMagnitude()).hasAValueNear( std::stold(actualData[i][2 + j]) );
            assertThat(rnemdData->electricField[j][i].getMagnitude()).hasAValueNear( std::stold(actualData[i][8 + j]) );
        }
    }
}

GTEST_TEST(testDataFieldParsing, logicOfDataFieldParsingIsSimplifiedSignificantlyWithParserClass)
{
    Utilities_API::Files::TextFile actualFile {"../../samples/rnemd/double.rnemd"};
    std::vector< std::vector<std::string> > actualData {actualFile.getSuperDataVector()};

    std::vector<std::string> outputTypes {"Cl-", "Na+", "SPCE_RB_0"};
    std::string_view sampleLabel {"#	z(Angstroms)	Temperature(K)	Velocity(angstroms/fs)			Density(g cm^-3)	Activity(unitless)(Cl-	Na+	)		Electric Field(kcal/mol/angstroms/e)			Electrostatic Potential(kcal/mol/e)"};

    DataFieldPtr rnemdAxis         { std::make_shared<DataField>("z(Angstroms)") };
    DataFieldPtr temperature       { std::make_shared<DataField>("Temperature(K)") };
    DataFieldPtr velocity          { std::make_shared<DataFieldArray>("Velocity(angstroms/fs)") };
    DataFieldPtr angularVelocity   { std::make_shared<DataFieldArray>("AngularVelocity(angstroms^2/fs)") };
    DataFieldPtr density           { std::make_shared<DataField>("Density(g cm^-3)") };
    DataFieldPtr activity          { std::make_shared<DataFieldVector>("Activity(unitless)", outputTypes) };
    DataFieldPtr electricField     { std::make_shared<DataFieldArray>("Electric Field(kcal/mol/angstroms/e)") };
    DataFieldPtr electricPotential { std::make_shared<DataField>("Electrostatic Potential(kcal/mol/e)") };

    DataFieldParser dataFieldParser { &actualFile, rnemdAxis,
                                                   temperature,
                                                   velocity,
                                                   angularVelocity,
                                                   density,
                                                   activity,
                                                   electricField,
                                                   electricPotential };

    dataFieldParser.parseDataFromFile(sampleLabel);


    RNEMDDataPtr rnemdData { std::make_shared<RNEMDData>() };

    rnemdAxis->convertToPhysicalQuantity(rnemdData->rnemdAxis);
    temperature->convertToPhysicalQuantity(rnemdData->temperature);
    dynamic_cast<DataFieldArray*>( velocity.get() )->convertToPhysicalQuantity(rnemdData->velocity);
    dynamic_cast<DataFieldArray*>( angularVelocity.get() )->convertToPhysicalQuantity(rnemdData->angularVelocity);
    density->convertToPhysicalQuantity(rnemdData->density);
    dynamic_cast<DataFieldVector*>( activity.get() )->convertToPhysicalQuantity(rnemdData->activity);
    dynamic_cast<DataFieldArray*>( electricField.get() )->convertToPhysicalQuantity(rnemdData->electricField);
    electricPotential->convertToPhysicalQuantity(rnemdData->electricPotential);

    for (std::size_t i {}; i < actualData[0].size(); ++i)
    {
        assertThat(rnemdData->rnemdAxis[i].getMagnitude()).hasAValueNear( std::stold(actualData[i][0]) );
        assertThat(rnemdData->temperature[i].getMagnitude()).hasAValueNear( std::stold(actualData[i][1]) );
        assertThat(rnemdData->density[i].getMagnitude()).hasAValueNear( std::stold(actualData[i][5]) );
        assertThat(rnemdData->activity[0][i].getMagnitude()).hasAValueNear( std::stold(actualData[i][6]) );
        assertThat(rnemdData->activity[1][i].getMagnitude()).hasAValueNear( std::stold(actualData[i][7]) );
        assertThat(rnemdData->electricPotential[i].getMagnitude()).hasAValueNear( std::stold(actualData[i][11]) );

        for (std::size_t j {}; j < 3; ++j)
        {
            assertThat(rnemdData->velocity[j][i].getMagnitude()).hasAValueNear( std::stold(actualData[i][2 + j]) );
            assertThat(rnemdData->electricField[j][i].getMagnitude()).hasAValueNear( std::stold(actualData[i][8 + j]) );
        }
    }
}
