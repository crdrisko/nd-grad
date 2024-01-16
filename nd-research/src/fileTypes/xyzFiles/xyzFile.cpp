// Copyright (c) 2019-2024 Cody R. Drisko. All rights reserved.
// Licensed under the MIT License. See the LICENSE file in the project root for more information.
//
// Name: xyzFile.cpp - Version 1.0.0
// Author: cdrisko
// Date: 02/24/2020-07:57:37
// Description: Funtion definitions for the XYZFile class

#include "xyzFile.hpp"

#include <cmath>
#include <cstddef>
#include <exception>
#include <iomanip>
#include <string>
#include <string_view>

#include <common-utils/files.hpp>
#include <common-utils/math.hpp>
#include <common-utils/strings.hpp>
#include <cpp-units/physicalQuantities.hpp>

using namespace CppUnits;

namespace ND_Research
{
    XYZFile::XYZFile(const std::filesystem::path& fileName_) : fileName {fileName_}
    {
        DryChem::FileParser parser {fileName};
        auto rows = parser.parseDataFile(DryChem::AsRows());

        std::size_t currentFrame {};

        do
        {
            parseInputXYZFile(rows, currentFrame++);
        } while (hasNextFrame(rows));
    }

    bool XYZFile::hasNextFrame(const std::vector<std::string>& rows_)
    {
        try
        {
            std::size_t atoms {};

            for (std::size_t frame {}; frame < params.inferred.numberOfFrames; ++frame)
                atoms += params.frame[frame].numberOfAtoms;

            std::string temp = rows_.at(atoms + (2 * params.inferred.numberOfFrames));
        }
        catch (const std::exception& e)
        {
            return false;
        }

        ++params.inferred.numberOfFrames;

        return true;
    }

    void XYZFile::parseInputXYZFile(const std::vector<std::string>& rows_, std::size_t currentFrame_)
    {
        static std::size_t startingLineNumber {};

        DryChem::Tokenizer tok {rows_[1 + startingLineNumber]};
        auto tokens = tok.split();

        params.frame.emplace_back(XYZParameters::XYZFrameParameters {std::stoul(rows_[startingLineNumber]),
            Time {tokens[0]},
            Matrix3D<CppUnits::Length> {{Length {tokens[1]}, Length {tokens[2]}, Length {tokens[3]}},
                {Length {tokens[4]}, Length {tokens[5]}, Length {tokens[6]}},
                {Length {tokens[7]}, Length {tokens[8]}, Length {tokens[9]}}}});

        data.resize(currentFrame_ + 1);

        for (std::size_t i {}; i < params.frame[currentFrame_].numberOfAtoms; ++i)
        {
            DryChem::Tokenizer tok {rows_[i + startingLineNumber + 2]};
            auto tokens = tok.split();

            data[currentFrame_].emplace_back(XYZData {tokens[0],
                DryChem::Vector3D<Length> {Length {tokens[1]}, Length {tokens[2]}, Length {tokens[3]}},
                DryChem::Vector3D<Velocity> {Velocity {tokens[4]}, Velocity {tokens[5]}, Velocity {tokens[6]}}});
        }

        startingLineNumber += (2 * (currentFrame_ + 1)) + params.frame[currentFrame_].numberOfAtoms;
    }

    void XYZFile::printOutputFile() const
    {
        std::ofstream outfile {fileName.parent_path() / ("new" + fileName.filename().string())};

        outfile << std::fixed << std::setprecision(8);

        outfile << params.frame[1].numberOfAtoms << '\n';
        outfile << std::setw(15) << params.frame[0].runTime;

        for (const auto& vec : params.frame[1].Hmat)
        {
            outfile << ";";

            for (const auto& vec1 : vec)
                outfile << std::setw(15) << vec1;
        }

        outfile << '\n';

        DryChem::Vector3D<long double> positions0 {}, positions1 {};

        for (std::size_t i {}; i < data[0].size(); ++i)
        {
            for (std::size_t j {}; j < data[1].size(); ++j)
            {
                for (std::size_t k {}; k < 3; ++k)
                {
                    positions0[k] = std::round(data[0][i].positions[k].getMagnitude());
                    positions1[k] = std::round(data[1][j].positions[k].getMagnitude());
                }

                auto [x0, y0, z0] = positions0;
                auto [x1, y1, z1] = positions1;

                if (x0 == x1 && y0 == y1 && z0 == z1)
                {
                    outfile << data[1][j].atomName << std::setw(15) << data[1][j].positions[0] << std::setw(15)
                            << data[1][j].positions[1] << std::setw(15) << data[1][j].positions[2] << std::setw(15)
                            << ((data[1][j].velocities[0] - data[0][i].velocities[0]) * 1e7) << std::setw(15)
                            << ((data[1][j].velocities[1] - data[0][i].velocities[1]) * 1e7) << std::setw(15)
                            << ((data[1][j].velocities[2] - data[0][i].velocities[2]) * 1e7) << '\n';
                    break;
                }
            }
        }
    }
}   // namespace ND_Research

int main(int argc, char* argv[])
{
    ND_Research::XYZFile file {argv[1]};

    file.printOutputFile();
}
