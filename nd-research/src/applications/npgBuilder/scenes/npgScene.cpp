// Copyright (c) 2019-2024 Cody R. Drisko. All rights reserved.
// Licensed under the MIT License. See the LICENSE file in the project root for more information.
//
// Name: npgScene.cpp
// Author: crdrisko
// Date: 11/13/2024-06:07:10
// Description:

#include "npgBuilder/scenes/npgScene.hpp"

#include <imgui-SFML.h>
#include <imgui.h>

#include <algorithm>
#include <cassert>
#include <iostream>

#include <common-utils/files.hpp>
#include <common-utils/strings.hpp>
#include <dryphys/math.hpp>
#include <dryphys/utilities.hpp>
#include <engine2d/action.hpp>
#include <engine2d/animation.hpp>
#include <engine2d/engine.hpp>
#include <engine2d/physics.hpp>
#include <engine2d/scene.hpp>

#include "npgBuilder/components.hpp"
#include "npgBuilder/forwardDeclare.hpp"

using namespace DryPhys::Literals;

namespace NPGBuilder
{
    NPGScene::NPGScene(Engine2D::Engine* gameEngine, const std::string& config) : Engine2D::Scene {gameEngine}
    {
        init(config);
    }

    void NPGScene::init(const std::string& config)
    {
        // Create the SFML window
        sf::ContextSettings settings;
        settings.antialiasingLevel = 8;

        auto& [name, width, height, fps, fullscreen] = game_->assets().getWindowConfig();

        config_.desiredBoxX = width;
        config_.desiredBoxY = height;

        registerAction(sf::Keyboard::Escape, "QUIT");

        // Parse input file
        const std::string punctuation {" \t\n,;'\"?!{}"};

        DryChem::FileParser parser {config};
        auto rows = parser.parseDataFile(DryChem::AsRows());

        for (const auto& row : rows)
        {
            DryChem::Tokenizer tok {row, punctuation};
            std::vector<std::string> splitRow = tok.split();

            switch (DryPhys::djb2Hash(splitRow[0].c_str()))
            {
            case "WordScale"_sID:
                config_.worldScale = std::stoul(splitRow[2]);
                break;
            case "HydrogenBondLength"_sID:
                config_.hydrogenBondLength = std::stof(splitRow[2]);
                break;
            case "HydrogenAtomRadius"_sID:
                config_.hydrogenAtomRadius = std::stof(splitRow[2]);
                break;
            case "CarbonBondLength"_sID:
                config_.carbonBondLength = std::stof(splitRow[2]);
                break;
            case "CarbonAtomRadius"_sID:
                config_.carbonAtomRadius = std::stof(splitRow[2]);
                break;
            case "Font"_sID:
                labelText_.setFont(game_->assets().getFont(splitRow[1]));
                labelText_.setCharacterSize(std::stoi(splitRow[3]));
                break;
            }
        }

        const float cos60 = 0.5f;
        const float sin60 = 0.5f * std::sqrt(3.0f);

        const float scaledBondLength = config_.worldScale * config_.carbonBondLength;

        const float worldScaledDistanceX = scaledBondLength * sin60;
        const float worldScaledDistanceY = scaledBondLength * cos60;

        float repeatX = std::round(config_.desiredBoxX / (2 * config_.carbonBondLength * sin60));
        float repeatY
            = std::round(config_.desiredBoxY / (2 * (config_.carbonBondLength * cos60 + config_.carbonBondLength)));

        boxSize_ = DryPhys::Vector3D {(2 * repeatX) * worldScaledDistanceX,
            (2 * repeatY) * (worldScaledDistanceY + scaledBondLength),
            0};

        // Offset ImGUI file bar by 30 pixels
        game_->window().create(sf::VideoMode(boxSize_.x, boxSize_.y + 30),
            name,
            (fullscreen + sf::Style::Default),
            settings);
        game_->window().setFramerateLimit(fps);

        // Don't create an imgui.ini file in each directory
        auto& imGuiIO {ImGui::GetIO()};

        imGuiIO.IniFilename = nullptr;
        imGuiIO.LogFilename = nullptr;

        entityManager_ = ConcreteEntityManager {};

        createGrapheneLattice();
    }

    void NPGScene::update()
    {
        // These systems should execute once every update
        entityManager_.update();

        if (!paused_)
        {
            sBonding();
            sPerformSwap();

            currentFrame_++;
        }
    }

    void NPGScene::postUpdate()
    {
        // These systems should execute once every render
        sGui();
    }

    void NPGScene::doActionImpl(const Engine2D::Action& action)
    {
        if (auto atype = action.type(); atype == Engine2D::Action::START)
        {
            switch (action.sid())
            {
            case "QUIT"_sID:
                onEnd();
                break;
            case "LEFT_CLICK"_sID:
            {
                for (auto& e : entityManager_.getEntities())
                {
                    if (isMouseWithin(e))
                    {
                        e->getComponent<CSelectable>().selected = true;

                        std::string at = e->getComponent<CTransform>().atomType;

                        atomTypes_[e->id()] = (e->tag() == "C" && at == "CB") ? "CB" : "CA";
                    }
                }
                break;
            }
            case "MIDDLE_CLICK"_sID:
            {
                for (auto& e : entityManager_.getEntities())
                {
                    if (isMouseWithin(e))
                    {
                        e->destroy();
                    }
                }
                break;
            }
            case "RIGHT_CLICK"_sID:
            {
                for (auto& e : entityManager_.getEntities())
                {
                    if (isMouseWithin(e))
                    {
                        e->getComponent<CSelectable>().selected = true;

                        atomTypes_[e->id()] = "HA";
                    }
                }
                break;
            }
            case "MOUSE_MOVE"_sID:
                mousePos_ = action.pos();
                break;
            default:
                break;
            }
        }
    }

    void NPGScene::render()
    {
        game_->window().clear();

        if (drawing_[BONDS])
        {
            for (const auto& bond : bonds_)
            {
                DryPhys::Vector3D pos1 = bond.first->getComponent<CTransform>().position;
                DryPhys::Vector3D pos2 = bond.second->getComponent<CTransform>().position;

                DryPhys::Vector3D diff = pos2 - pos1;

                if (diff.magnitudeSquared() <= 1690.0f)
                    drawLine(pos1, pos2);
            }
        }

        for (auto entity : entityManager_.getEntities())
        {
            auto& eTransform = entity->getComponent<CTransform>();
            auto& circle     = entity->getComponent<CShape>().circle;

            circle.setPosition(eTransform.position.x, eTransform.position.y);

            game_->window().draw(circle);

            if (determineLabelType(0b01110))
            {
                sf::FloatRect textBoundingBox = labelText_.getGlobalBounds();

                labelText_.setOrigin(0.5f * textBoundingBox.width, 0.5f * textBoundingBox.height);
                labelText_.setPosition(eTransform.position.x, eTransform.position.y);

                if (drawing_[LABELS])
                    labelText_.setString(std::to_string(entity->id()));

                else if (drawing_[ATOMTYPES])
                    labelText_.setString(eTransform.atomType);

                else if (drawing_[BONDORDER])
                    labelText_.setString(std::to_string(entity->getComponent<CBonds>().currentBonds));

                labelText_.setFillColor(sf::Color::Green);

                game_->window().draw(labelText_);
            }
        }

        if (drawing_[SCALE])
        {
            drawLine(10.0f, 1195.0f, 10.0f, 1205.0f, sf::Color::White);
            drawLine(10.0f, 1200.0f, 40.0f, 1200.0f, sf::Color::White);

            drawLine(40.0f, 1195.0f, 40.0f, 1205.0f, sf::Color::White);
            drawLine(40.0f, 1200.0f, 70.0f, 1200.0f, sf::Color::White);

            drawLine(70.0f, 1195.0f, 70.0f, 1205.0f, sf::Color::White);
            drawLine(70.0f, 1200.0f, 100.0f, 1200.0f, sf::Color::White);

            drawLine(100.0f, 1195.0f, 100.0f, 1205.0f, sf::Color::White);
        }

        // Print a dot in the center of the window as a reference point
        sf::Vector2u windowSize = game_->window().getSize();
        DryPhys::Vector3D centerOfWindowPosition {windowSize.x / 2.0f, windowSize.y / 2.0f, 0};

        sf::CircleShape centerOfWindow(5.0f);

        centerOfWindow.setOrigin(2.5f, 2.5f);
        centerOfWindow.setFillColor(sf::Color::Red);
        centerOfWindow.setPosition(centerOfWindowPosition.x + 7.5f, centerOfWindowPosition.y + 12.5f);

        game_->window().draw(centerOfWindow);
    }

    void NPGScene::onEnd() { game_->quit(); }

    void NPGScene::sGui()
    {
        // ImGui::ShowDemoWindow();

        if (ImGui::BeginMainMenuBar())
        {
            if (ImGui::BeginMenu("File"))
            {
                if (ImGui::MenuItem("New"))
                {
                    createGrapheneLattice();
                }
                if (ImGui::MenuItem("Open", "Ctrl+O", false, false))
                {
                }
                ImGui::Separator();
                if (ImGui::MenuItem("Save", "Ctrl+S"))
                {
                    std::string tempStr;

                    if (!outputFileName_.empty())
                        tempStr = outputFileName_.substr(outputFileName_.size() - 3);

                    if (tempStr == "omd")
                    {
                        writeOMDFile(outputFileName_);
                    }
                    else if (tempStr == "xyz")
                    {
                        writeXYZFile(outputFileName_);
                    }
                    else
                    {
                        std::cout << "Unknown file extension. Allowed types are .xyz or .omd\n";
                    }
                }
                if (ImGui::BeginMenu("Save As.."))
                {
                    static char str0[128] = "graphene.omd";
                    ImGui::InputText("", str0, IM_ARRAYSIZE(str0));
                    ImGui::EndMenu();

                    outputFileName_ = str0;
                }
                ImGui::Separator();
                if (ImGui::MenuItem("Quit", "Esc"))
                {
                    onEnd();
                }
                ImGui::EndMenu();
            }

            if (ImGui::BeginMenu("Edit"))
            {
                if (ImGui::MenuItem("Undo", "CTRL+Z"))
                {
                    canRedo_ = true;
                }
                if (ImGui::MenuItem("Redo", "CTRL+Y", false, canRedo_))
                {
                    canRedo_ = false;
                }
                ImGui::EndMenu();
            }

            if (ImGui::BeginMenu("View"))
            {
                if (ImGui::MenuItem("Show/Hide Bonds"))
                {
                    drawing_.flip(BONDS);
                }
                if (ImGui::BeginMenu("Show/Hide Lables"))
                {
                    if (ImGui::MenuItem("Atom Labels"))
                    {
                        drawing_.flip(LABELS);
                        drawing_.set(ATOMTYPES, false);
                        drawing_.set(BONDORDER, false);
                    }
                    if (ImGui::MenuItem("Atom Types"))
                    {
                        drawing_.flip(ATOMTYPES);
                        drawing_.set(LABELS, false);
                        drawing_.set(BONDORDER, false);
                    }
                    if (ImGui::MenuItem("Bond Order"))
                    {
                        drawing_.flip(BONDORDER);
                        drawing_.set(LABELS, false);
                        drawing_.set(ATOMTYPES, false);
                    }
                    ImGui::EndMenu();
                }
                if (ImGui::MenuItem("Show/Hide Scale"))
                {
                    drawing_.flip(SCALE);
                }
                ImGui::EndMenu();
            }

            ImGui::EndMainMenuBar();
        }
    }

    void NPGScene::sBonding()
    {
        // Unset current bonds_ before recalculating
        bonds_.clear();

        std::size_t count {};
        for (auto& entity : entityManager_.getEntities())
        {
            auto& eBond  = entity->getComponent<CBonds>();
            entity->id() = count++;

            eBond.currentBonds = 0;
        }

        for (auto& entity : entityManager_.getEntities())
        {
            calculateBonds(entity);
        }

        // After all bonds_ have been calculated, we need to figure out who's missing bonds_
        for (auto& e1 : entityManager_.getEntities("C"))
        {
            auto& e1Bond = e1->getComponent<CBonds>();

            if (e1Bond.currentBonds != e1Bond.maxBonds)
            {
                auto& e1Trans = e1->getComponent<CTransform>();

                if (std::fabs(e1Trans.position.x - maxPos_.x) < std::numeric_limits<float>::epsilon())
                {
                    DryPhys::Vector3D newPosition {e1Trans.position.x - boxSize_.x, e1Trans.position.y, 0};

                    // Can't use calculateBonds() as is, due to the corners
                    for (auto& e2 : entityManager_.getEntities("C"))
                    {
                        if (e1 != e2)
                        {
                            auto& e2Trans = e2->getComponent<CTransform>();
                            auto& e2Bond  = e2->getComponent<CBonds>();

                            DryPhys::Vector3D condition;

                            if (std::fabs(e2Trans.position.y - maxPos_.y) < std::numeric_limits<float>::epsilon())
                            {
                                DryPhys::Vector3D newPosition2 {e2Trans.position.x, e2Trans.position.y - boxSize_.y, 0};

                                condition = newPosition2 - newPosition;
                            }
                            else
                            {
                                condition = e2Trans.position - newPosition;
                            }

                            if (condition.magnitudeSquared() <= 1690.0f)
                            {
                                e1Bond.currentBonds++;
                                e2Bond.currentBonds++;

                                bonds_.push_back(std::make_pair(e1, e2));
                            }
                        }
                    }
                }

                if (std::fabs(e1Trans.position.y - maxPos_.y) < std::numeric_limits<float>::epsilon())
                {
                    DryPhys::Vector3D tempPosition = e1Trans.position;

                    e1Trans.position = DryPhys::Vector3D {e1Trans.position.x, e1Trans.position.y - boxSize_.y, 0};

                    calculateBonds(e1);

                    e1Trans.position = tempPosition;
                }
            }
        }
    }

    void NPGScene::sPerformSwap()
    {
        for (auto& entity : entityManager_.getEntities())
        {
            if (entity->getComponent<CSelectable>().selected)
            {
                auto eTrans = entity->getComponent<CTransform>();

                DryPhys::Vector3D pos = eTrans.position;

                entity->destroy();

                if (atomTypes_[entity->id()] == "CB")
                {
                    auto carbonAtom = entityManager_.addEntity("C");

                    carbonAtom->addComponent<CTransform>(pos, "CA");
                    carbonAtom->addComponent<CShape>(config_.carbonAtomRadius, sf::Color::Blue);
                    carbonAtom->addComponent<CBonds>(3);
                    carbonAtom->addComponent<CSelectable>();
                }
                else if (atomTypes_[entity->id()] == "CA")
                {
                    auto carbonAtom = entityManager_.addEntity("C");

                    carbonAtom->addComponent<CTransform>(pos, "CB");
                    carbonAtom->addComponent<CShape>(config_.carbonAtomRadius, sf::Color(128, 128, 128));
                    carbonAtom->addComponent<CBonds>(3);
                    carbonAtom->addComponent<CSelectable>();
                }
                else
                {
                    auto hydrogenAtom = entityManager_.addEntity("H");

                    hydrogenAtom->addComponent<CTransform>(pos, "HA");
                    hydrogenAtom->addComponent<CShape>(config_.hydrogenAtomRadius, sf::Color::White);
                    hydrogenAtom->addComponent<CBonds>(1);
                    hydrogenAtom->addComponent<CSelectable>();
                }
            }
        }
    }

    void NPGScene::createGrapheneLattice()
    {
        for (auto e : entityManager_.getEntities())
            e->destroy();

        const float cos60 = 0.5f;
        const float sin60 = 0.5f * std::sqrt(3.0f);

        const float scaledBondLength = config_.worldScale * config_.carbonBondLength;

        const float worldScaledDistanceX = scaledBondLength * sin60;
        const float worldScaledDistanceY = scaledBondLength * cos60;

        float repeatX = std::round(config_.desiredBoxX / (2 * config_.carbonBondLength * sin60));
        float repeatY
            = std::round(config_.desiredBoxY / (2 * (config_.carbonBondLength * cos60 + config_.carbonBondLength)));

        for (std::size_t i {}; i < repeatY; ++i)
        {
            float verticalOffset = i * (2 * worldScaledDistanceY + 2 * scaledBondLength) + 3 * config_.carbonAtomRadius;

            for (std::size_t j {}; j < repeatX; ++j)
            {
                float horizontalOffset = 2 * j * worldScaledDistanceX + config_.carbonAtomRadius;

                auto carbonAtom1 = entityManager_.addEntity("C");

                auto trans1 = carbonAtom1->addComponent<CTransform>(
                    DryPhys::Vector3D {worldScaledDistanceX + horizontalOffset, verticalOffset, 0},
                    "CB");
                carbonAtom1->addComponent<CShape>(config_.carbonAtomRadius, sf::Color(128, 128, 128));
                carbonAtom1->addComponent<CBonds>(3);
                carbonAtom1->addComponent<CSelectable>();

                auto carbonAtom2 = entityManager_.addEntity("C");

                carbonAtom2->addComponent<CTransform>(
                    DryPhys::Vector3D {worldScaledDistanceX + horizontalOffset, verticalOffset + scaledBondLength, 0},
                    "CB");
                carbonAtom2->addComponent<CShape>(config_.carbonAtomRadius, sf::Color(128, 128, 128));
                carbonAtom2->addComponent<CBonds>(3);
                carbonAtom2->addComponent<CSelectable>();

                auto carbonAtom3 = entityManager_.addEntity("C");

                carbonAtom3->addComponent<CTransform>(
                    DryPhys::Vector3D {horizontalOffset, worldScaledDistanceY + verticalOffset + scaledBondLength, 0},
                    "CB");
                carbonAtom3->addComponent<CShape>(config_.carbonAtomRadius, sf::Color(128, 128, 128));
                carbonAtom3->addComponent<CBonds>(3);
                carbonAtom3->addComponent<CSelectable>();

                auto carbonAtom4 = entityManager_.addEntity("C");

                auto trans4 = carbonAtom4->addComponent<CTransform>(
                    DryPhys::Vector3D {horizontalOffset, worldScaledDistanceY + verticalOffset + 2 * scaledBondLength, 0},
                    "CB");
                carbonAtom4->addComponent<CShape>(config_.carbonAtomRadius, sf::Color(128, 128, 128));
                carbonAtom4->addComponent<CBonds>(3);
                carbonAtom4->addComponent<CSelectable>();

                // Store the maximum X and Y coordinates for bonding across periodic boundary conditions
                if (i == 0 && j == (repeatX - 1))
                    maxPos_.x = trans1.position.x;

                if (i == (repeatY - 1) && j == 0)
                    maxPos_.y = trans4.position.y;
            }
        }
    }

    void NPGScene::calculateBonds(ConcreteEntityPtr entity)
    {
        auto& eTransform = entity->getComponent<CTransform>();
        auto& eBond      = entity->getComponent<CBonds>();

        for (auto& e2 : entityManager_.getEntities("C"))
        {
            if (entity != e2)
            {
                auto& e2Transform = e2->getComponent<CTransform>();
                auto& e2Bond      = e2->getComponent<CBonds>();

                DryPhys::Vector3D diff = e2Transform.position - eTransform.position;

                if (entity->tag() == "C")
                {
                    if (eTransform.position.y < e2Transform.position.y && diff.magnitudeSquared() <= 1690.0f)
                    {
                        eBond.currentBonds++;
                        e2Bond.currentBonds++;
                        bonds_.push_back(std::make_pair(entity, e2));
                    }
                }
                else if (entity->tag() == "H")
                {
                    if (diff.magnitudeSquared() <= 1690.0f)
                    {
                        eBond.currentBonds++;
                        e2Bond.currentBonds++;
                        bonds_.push_back(std::make_pair(entity, e2));
                    }
                }
            }
        }
    }

    void NPGScene::writeXYZFile(const std::string& fileName)
    {
        std::ofstream outputFile;
        outputFile.open(fileName);

        outputFile << entityManager_.getEntities().size() << "\n\t0.00000000;  " << boxSize_.x / config_.worldScale
                   << "   0.00000000   0.00000000;   0.00000000  " << boxSize_.y / config_.worldScale
                   << "   0.00000000;   0.00000000   0.00000000  40.00000000\n";

        outputFile.precision(10);

        for (const auto& entity : entityManager_.getEntities())
        {
            auto eTransform = entity->getComponent<CTransform>();

            outputFile << eTransform.atomType << '\t'
                       << ((eTransform.position.x - config_.carbonAtomRadius) / config_.worldScale) << '\t'
                       << ((eTransform.position.y - 3 * config_.carbonAtomRadius) / config_.worldScale) << "\t0.00000000\n";
        }
    }

    void NPGScene::writeOMDFile(const std::string& fileName)
    {
        std::string baseFileName = fileName.substr(0, fileName.size() - 4);

        std::string upperBaseFileName;

        for (const auto& ch : baseFileName)
            upperBaseFileName += std::toupper(ch);

        std::ofstream omdOutputFile, incOutputFile;

        omdOutputFile.open(baseFileName + ".omd");
        incOutputFile.open(baseFileName + ".inc");

        omdOutputFile
            << "<OpenMD version=3>\n  <MetaData>\n\n#include \"" << baseFileName << ".inc\"\n"
            << "\ncomponent{\n  type = \"" << baseFileName << "\"; \n  nMol = 1; \n }\n"
            << "\nminimizer {\n  useMinimizer = true;\n  method = \"SD\";\n}\n"
            << "\nforceField = \"graphene\";\n// ensemble = NVT;\ncutoffMethod = \"shifted_force\";\n"
            << "electrostaticScreeningMethod = \"damped\";\ncutoffRadius = 12;\ndampingAlpha = 0.18;\n"
            << "targetTemp = 300;\ntauThermostat = 1000;\ndt = 1.0;\nrunTime = 1e3;\nsampleTime = 500;\nstatusTime = 10;\n"
            << "\nzconsTime = 1;\nzconsTol = 0.01;\n\nzconstraint {\n  molIndex = 0;\n  kRatio = 0;\n  zPos = 30.0;\n}\n"
            << "  </MetaData>\n  <Snapshot>\n    <FrameData>\n      Time: 0\n"
            << "      Hmat: {{ " << boxSize_.x / config_.worldScale << ", 0, 0 }, { 0, " << boxSize_.y / config_.worldScale
            << ", 0 }, { 0, 0, 40.0 }}\n    </FrameData>\n    <StuntDoubles>\n";

        incOutputFile << "// Built using NPG-Builder\n#ifndef " << upperBaseFileName << "_INC\n#define " << upperBaseFileName
                      << "_INC\n\nmolecule{\n  name = \"" << baseFileName << "\";\n\n";

        for (const auto& entity : entityManager_.getEntities())
        {
            auto eTransform = entity->getComponent<CTransform>();

            float posX = (eTransform.position.x - config_.carbonAtomRadius) / config_.worldScale;
            float posY = (eTransform.position.y - 3 * config_.carbonAtomRadius) / config_.worldScale;

            omdOutputFile << '\t' << entity->id() << "\tpv\t" << posX << '\t' << posY
                          << "\t0\t0.000000e+00\t0.000000e+00\t0.000000e+00\n";

            incOutputFile << "  atom[" << entity->id() << "] { type = \"" << eTransform.atomType << "\"; position( " << posX
                          << ", " << posY << ", 0); }\n";
        }

        incOutputFile << "\n  // This list includes bonds_ that span the box\n";

        for (const auto& bond : bonds_)
            incOutputFile << "  bond { members(" << bond.first->id() << ", " << bond.second->id() << "); }\n";

        omdOutputFile << "    </StuntDoubles>\n  </Snapshot>\n</OpenMD>\n";
        incOutputFile << "}\n\n#endif\n";
    }

    bool NPGScene::isMouseWithin(ConcreteEntityPtr entity) const
    {
        DryPhys::Vector3D pos = entity->getComponent<CTransform>().position;
        float radius          = entity->getComponent<CShape>().circle.getRadius();

        if (mousePos_.x > pos.x - radius && mousePos_.x < pos.x + radius && mousePos_.y > pos.y - radius
            && mousePos_.y < pos.y + radius)
        {
            return true;
        }

        return false;
    }

    bool NPGScene::determineLabelType(unsigned int mask) const
    {
        bool result {};

        DrawingBitSet b1 {drawing_}, b2 {mask};

        b1 &= b2;

        for (std::size_t bit {}; bit < b2.size(); ++bit)
            if (b2.test(bit))
                result = (!result != !b1.test(bit));   // Logical XOR

        return result;
    }
}   // namespace NPGBuilder
