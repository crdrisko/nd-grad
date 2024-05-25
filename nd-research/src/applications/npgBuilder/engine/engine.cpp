// Copyright (c) 2019-2024 Cody R. Drisko. All rights reserved.
// Licensed under the MIT License. See the LICENSE file in the project root for more information.
//
// Name: engine.cpp - Version 1.0.0
// Author: crdrisko
// Date: 04/17/2024-08:09:47
// Description:

#include "npgBuilder/engine.hpp"

#include <imgui-SFML.h>
#include <imgui.h>

#include <fstream>
#include <iostream>
#include <memory>
#include <string>

#include <SFML/Graphics.hpp>
#include <common-utils/files.hpp>
#include <common-utils/strings.hpp>

#include "npgBuilder/action.hpp"

Engine::Engine(const std::string& config) { init(config); }

void Engine::init(const std::string& config)
{
    const std::string punctuation {" \t\n,;'\"?!{}"};

    DryChem::FileParser parser {config};
    auto rows = parser.parseDataFile(DryChem::AsRows());

    for (const auto& row : rows)
    {
        DryChem::Tokenizer tok {row, punctuation};
        std::vector<std::string> splitRow = tok.split();

        if (splitRow[0] == "WordScale")
        {
            config_.worldScale = std::stoul(splitRow[2]);
        }
        else if (splitRow[0] == "DesiredBoxDimensions")
        {
            config_.desiredBoxX = std::stoul(splitRow[2]);
            config_.desiredBoxY = std::stoul(splitRow[3]);
        }
        else if (splitRow[0] == "HydrogenBondLength")
        {
            config_.hydrogenBondLength = std::stof(splitRow[2]);
        }
        else if (splitRow[0] == "HydrogenAtomRadius")
        {
            config_.hydrogenAtomRadius = std::stof(splitRow[2]);
        }
        else if (splitRow[0] == "CarbonBondLength")
        {
            config_.carbonBondLength = std::stof(splitRow[2]);
        }
        else if (splitRow[0] == "CarbonAtomRadius")
        {
            config_.carbonAtomRadius = std::stof(splitRow[2]);
        }
        else if (splitRow[0] == "Font")
        {
            if (!font_.loadFromFile(splitRow[1]))
            {
                std::cerr << "Could not load font: " << splitRow[1] << '\n';
                std::exit(EXIT_FAILURE);
            }

            labelText_.setFont(font_);
            labelText_.setCharacterSize(std::stoi(splitRow[2]));
        }
    }

    const float cos60 = 0.5f;
    const float sin60 = 0.5f * std::sqrt(3.0f);

    const float scaledBondLength = config_.worldScale * config_.carbonBondLength;

    const float worldScaledDistanceX = scaledBondLength * sin60;
    const float worldScaledDistanceY = scaledBondLength * cos60;

    float repeatX = std::round(config_.desiredBoxX / (2 * config_.carbonBondLength * sin60));
    float repeatY = std::round(config_.desiredBoxY / (2 * (config_.carbonBondLength * cos60 + config_.carbonBondLength)));

    boxSize_ = Vec2 {(2 * repeatX) * worldScaledDistanceX, (2 * repeatY) * (worldScaledDistanceY + scaledBondLength)};

    // Create the SFML window
    window_.create(sf::VideoMode(boxSize_.x, boxSize_.y + 30), "Graphene Builder");   // Offset ImGUI file bar by 30 pixels

    window_.setFramerateLimit(60);
    if (!ImGui::SFML::Init(window_))
        std::exit(EXIT_FAILURE);

    // Don't create an imgui.ini file in each directory
    auto& imGuiIO {ImGui::GetIO()};

    imGuiIO.IniFilename = nullptr;
    imGuiIO.LogFilename = nullptr;

    registerAction(sf::Keyboard::Escape, "QUIT");

    registerAction(sf::Mouse::Left, "LEFT_CLICK");
    registerAction(sf::Mouse::Middle, "MIDDLE_CLICK");
    registerAction(sf::Mouse::Right, "RIGHT_CLICK");


    createGrapheneLattice();
}

void Engine::quit() { running_ = false; }

void Engine::run()
{
    sf::Clock deltaClock;
    while (isRunning())
    {
        ImGui::SFML::Update(window_, deltaClock.restart());

        entityManager_.update();

        sUserInput();
        sGui();
        sBonding();
        sPerformSwap();
        sRender();
    }

    ImGui::SFML::Shutdown();
}

void Engine::sUserInput()
{
    sf::Event event;
    while (window_.pollEvent(event))
    {
        ImGui::SFML::ProcessEvent(window_, event);

        if (event.type == sf::Event::Closed)
        {
            quit();
        }

        if (event.type == sf::Event::KeyPressed || event.type == sf::Event::KeyReleased)
        {
            // if the current scene does not have an action associated with this key, skip the event
            if (actionMap_.find(event.key.code) == actionMap_.end())
            {
                continue;
            }

            // determine start or end action by whether it was a key press or release
            const std::string actionType = (event.type == sf::Event::KeyPressed) ? "START" : "END";

            // look up the action and send the action to the scene
            sDoAction(Action(actionMap_.at(event.key.code), actionType));
        }

        auto mousePos = sf::Mouse::getPosition(window_);
        Vec2 mpos(mousePos.x, mousePos.y);

        if (event.type == sf::Event::MouseButtonPressed)
        {
            switch (event.mouseButton.button)
            {
            case sf::Mouse::Left:
            {
                sDoAction(Action {"LEFT_CLICK", "START", mpos});
                break;
            }
            case sf::Mouse::Middle:
            {
                sDoAction(Action {"MIDDLE_CLICK", "START", mpos});
                break;
            }
            case sf::Mouse::Right:
            {
                sDoAction(Action {"RIGHT_CLICK", "START", mpos});
                break;
            }
            default:
                break;
            }
        }

        if (event.type == sf::Event::MouseButtonReleased)
        {
            switch (event.mouseButton.button)
            {
            case sf::Mouse::Left:
            {
                sDoAction(Action {"LEFT_CLICK", "END", mpos});
                break;
            }
            case sf::Mouse::Middle:
            {
                sDoAction(Action {"MIDDLE_CLICK", "END", mpos});
                break;
            }
            case sf::Mouse::Right:
            {
                sDoAction(Action {"RIGHT_CLICK", "END", mpos});
                break;
            }
            default:
                break;
            }
        }

        if (event.type == sf::Event::MouseMoved)
        {
            sDoAction(Action {"MOUSE_MOVE", Vec2(event.mouseMove.x, event.mouseMove.y)});
        }
    }
}

void Engine::sDoAction(const Action& action)
{
    if (action.name() == "MOUSE_MOVE")
    {
        mousePos_ = action.pos();
    }

    if (action.type() == "START")
    {
        if (action.name() == "QUIT")
        {
            quit();
        }

        else if (action.name() == "LEFT_CLICK")
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
        }
        else if (action.name() == "MIDDLE_CLICK")
        {
            for (auto& e : entityManager_.getEntities())
            {
                if (isMouseWithin(e))
                {
                    e->destroy();
                }
            }
        }
        else if (action.name() == "RIGHT_CLICK")
        {
            for (auto& e : entityManager_.getEntities())
            {
                if (isMouseWithin(e))
                {
                    e->getComponent<CSelectable>().selected = true;

                    atomTypes_[e->id()] = "HA";
                }
            }
        }
    }
}

void Engine::sGui()
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
                quit();
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

void Engine::sBonding()
{
    // Unset current bonds_ before recalculating
    bonds_.clear();

    std::size_t count {};
    for (auto e : entityManager_.getEntities())
    {
        auto& eBond = e->getComponent<CBonds>();
        e->id()     = count++;

        eBond.currentBonds = 0;
    }

    for (auto e : entityManager_.getEntities())
    {
        calculateBonds(e);
    }

    // After all bonds_ have been calculated, we need to figure out who's missing bonds_
    for (auto e : entityManager_.getEntities("C"))
    {
        auto& eBond = e->getComponent<CBonds>();

        if (eBond.currentBonds != eBond.maxBonds)
        {
            auto& eTrans = e->getComponent<CTransform>();

            if (std::fabs(eTrans.position.x - maxPos_.x) < std::numeric_limits<float>::epsilon())
            {
                Vec2 newPosition {eTrans.position.x - boxSize_.x, eTrans.position.y};

                // Can't use calculateBonds() as is, due to the corners
                for (auto e2 : entityManager_.getEntities("C"))
                {
                    if (e != e2)
                    {
                        auto& e2Transform = e2->getComponent<CTransform>();
                        auto& e2Bond      = e2->getComponent<CBonds>();

                        float condition {};

                        if (std::fabs(e2Transform.position.y - maxPos_.y) < std::numeric_limits<float>::epsilon())
                        {
                            // auto& eBond = e->getComponent<CBonds>();

                            Vec2 newPosition2 {e2Transform.position.x, e2Transform.position.y - boxSize_.y};

                            condition = newPosition.distSquared(newPosition2);
                        }
                        else
                        {
                            condition = newPosition.distSquared(e2Transform.position);
                        }

                        if (condition <= 1690.0f)
                        {
                            eBond.currentBonds++;
                            e2Bond.currentBonds++;
                            bonds_.push_back(std::make_pair(e, e2));
                        }
                    }
                }
            }

            if (std::fabs(eTrans.position.y - maxPos_.y) < std::numeric_limits<float>::epsilon())
            {
                Vec2 tempPosition = eTrans.position;

                eTrans.position = Vec2 {eTrans.position.x, eTrans.position.y - boxSize_.y};

                calculateBonds(e);

                eTrans.position = tempPosition;
            }
        }
    }
}

void Engine::sPerformSwap()
{
    for (auto& entity : entityManager_.getEntities())
    {
        if (entity->getComponent<CSelectable>().selected)
        {
            auto eTrans = entity->getComponent<CTransform>();

            Vec2 pos = eTrans.position;

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

void Engine::sRender()
{
    window_.clear();

    if (drawing_[BONDS])
    {
        for (const auto& bond : bonds_)
        {
            Vec2 pos1 = bond.first->getComponent<CTransform>().position;
            Vec2 pos2 = bond.second->getComponent<CTransform>().position;

            if (pos1.distSquared(pos2) <= 1690.0f)
                drawLine(pos1, pos2);
        }
    }

    for (auto e : entityManager_.getEntities())
    {
        auto& eTransform = e->getComponent<CTransform>();
        auto& circle     = e->getComponent<CShape>().circle;

        circle.setPosition(eTransform.position.x, eTransform.position.y);

        window_.draw(circle);

        if (determineLabelType(0b01110))
        {
            sf::FloatRect textBoundingBox = labelText_.getGlobalBounds();

            labelText_.setOrigin(0.5f * textBoundingBox.width, 0.5f * textBoundingBox.height);
            labelText_.setPosition(eTransform.position.x, eTransform.position.y);

            if (drawing_[LABELS])
                labelText_.setString(std::to_string(e->id()));

            else if (drawing_[ATOMTYPES])
                labelText_.setString(eTransform.atomType);

            else if (drawing_[BONDORDER])
                labelText_.setString(std::to_string(e->getComponent<CBonds>().currentBonds));

            labelText_.setFillColor(sf::Color::Green);

            window_.draw(labelText_);
        }
    }

    sf::Vector2u windowSize = window_.getSize();
    Vec2 centerOfWindowPosition {windowSize.x / 2.0f, windowSize.y / 2.0f};

    if (drawing_[SCALE])
    {
        drawLine(Vec2 {10.0f, 1195.0f}, Vec2 {10.0f, 1205.0f});
        drawLine(Vec2 {10.0f, 1200.0f}, Vec2 {40.0f, 1200.0f});

        drawLine(Vec2 {40.0f, 1195.0f}, Vec2 {40.0f, 1205.0f});
        drawLine(Vec2 {40.0f, 1200.0f}, Vec2 {70.0f, 1200.0f});

        drawLine(Vec2 {70.0f, 1195.0f}, Vec2 {70.0f, 1205.0f});
        drawLine(Vec2 {70.0f, 1200.0f}, Vec2 {100.0f, 1200.0f});

        drawLine(Vec2 {100.0f, 1195.0f}, Vec2 {100.0f, 1205.0f});
    }

    // Print a dot in the center of the window as a reference point
    sf::CircleShape centerOfWindow(5.0f);

    centerOfWindow.setOrigin(2.5f, 2.5f);
    centerOfWindow.setFillColor(sf::Color::Red);
    centerOfWindow.setPosition(centerOfWindowPosition.x + 7.5f, centerOfWindowPosition.y + 12.5f);

    window_.draw(centerOfWindow);

    ImGui::SFML::Render(window_);
    window_.display();
}

void Engine::createGrapheneLattice()
{
    for (auto e : entityManager_.getEntities())
        e->destroy();

    const float cos60 = 0.5f;
    const float sin60 = 0.5f * std::sqrt(3.0f);

    const float scaledBondLength = config_.worldScale * config_.carbonBondLength;

    const float worldScaledDistanceX = scaledBondLength * sin60;
    const float worldScaledDistanceY = scaledBondLength * cos60;

    float repeatX = std::round(config_.desiredBoxX / (2 * config_.carbonBondLength * sin60));
    float repeatY = std::round(config_.desiredBoxY / (2 * (config_.carbonBondLength * cos60 + config_.carbonBondLength)));

    for (std::size_t i {}; i < repeatY; ++i)
    {
        float verticalOffset = i * (2 * worldScaledDistanceY + 2 * scaledBondLength) + 3 * config_.carbonAtomRadius;

        for (std::size_t j {}; j < repeatX; ++j)
        {
            float horizontalOffset = 2 * j * worldScaledDistanceX + config_.carbonAtomRadius;

            auto carbonAtom1 = entityManager_.addEntity("C");

            carbonAtom1->addComponent<CTransform>(Vec2(worldScaledDistanceX + horizontalOffset, verticalOffset), "CB");
            carbonAtom1->addComponent<CShape>(config_.carbonAtomRadius, sf::Color(128, 128, 128));
            carbonAtom1->addComponent<CBonds>(3);
            carbonAtom1->addComponent<CSelectable>();

            auto carbonAtom2 = entityManager_.addEntity("C");

            carbonAtom2->addComponent<CTransform>(
                Vec2(worldScaledDistanceX + horizontalOffset, verticalOffset + scaledBondLength),
                "CB");
            carbonAtom2->addComponent<CShape>(config_.carbonAtomRadius, sf::Color(128, 128, 128));
            carbonAtom1->addComponent<CBonds>(3);
            carbonAtom2->addComponent<CSelectable>();

            auto carbonAtom3 = entityManager_.addEntity("C");

            carbonAtom3->addComponent<CTransform>(
                Vec2(horizontalOffset, worldScaledDistanceY + verticalOffset + scaledBondLength),
                "CB");
            carbonAtom3->addComponent<CShape>(config_.carbonAtomRadius, sf::Color(128, 128, 128));
            carbonAtom1->addComponent<CBonds>(3);
            carbonAtom3->addComponent<CSelectable>();

            auto carbonAtom4 = entityManager_.addEntity("C");

            carbonAtom4->addComponent<CTransform>(
                Vec2(horizontalOffset, worldScaledDistanceY + verticalOffset + 2 * scaledBondLength),
                "CB");
            carbonAtom4->addComponent<CShape>(config_.carbonAtomRadius, sf::Color(128, 128, 128));
            carbonAtom1->addComponent<CBonds>(3);
            carbonAtom4->addComponent<CSelectable>();

            // Store the maximum X and Y coordinates for bonding across periodic boundary conditions
            if (i == 0 && j == (repeatX - 1))
                maxPos_.x = carbonAtom1->getComponent<CTransform>().position.x;

            if (i == (repeatY - 1) && j == 0)
                maxPos_.y = carbonAtom4->getComponent<CTransform>().position.y;
        }
    }
}

void Engine::calculateBonds(const std::shared_ptr<Entity>& e)
{
    auto& eTransform = e->getComponent<CTransform>();
    auto& eBond      = e->getComponent<CBonds>();

    for (auto e2 : entityManager_.getEntities("C"))
    {
        if (e != e2)
        {
            if (e->tag() == "C")
            {
                auto& e2Transform = e2->getComponent<CTransform>();
                auto& e2Bond      = e2->getComponent<CBonds>();

                if (eTransform.position.y < e2Transform.position.y
                    && eTransform.position.distSquared(e2Transform.position) <= 1690.0f)
                {
                    eBond.currentBonds++;
                    e2Bond.currentBonds++;
                    bonds_.push_back(std::make_pair(e, e2));
                }
            }
            else if (e->tag() == "H")
            {
                auto& e2Transform = e2->getComponent<CTransform>();
                auto& e2Bond      = e2->getComponent<CBonds>();

                if (eTransform.position.distSquared(e2Transform.position) <= 1690.0f)
                {
                    eBond.currentBonds++;
                    e2Bond.currentBonds++;
                    bonds_.push_back(std::make_pair(e, e2));
                }
            }
        }
    }
}

void Engine::writeXYZFile(const std::string& fileName)
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

void Engine::writeOMDFile(const std::string& fileName)
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

bool Engine::isMouseWithin(std::shared_ptr<Entity> e) const
{
    Vec2 pos     = e->getComponent<CTransform>().position;
    float radius = e->getComponent<CShape>().circle.getRadius();

    if (mousePos_.x > pos.x - radius && mousePos_.x < pos.x + radius && mousePos_.y > pos.y - radius
        && mousePos_.y < pos.y + radius)
    {
        return true;
    }

    return false;
}

void Engine::drawLine(const Vec2& p1, const Vec2& p2)
{
    sf::Vertex line[] = {sf::Vector2f(p1.x, p1.y), sf::Vector2f(p2.x, p2.y)};
    window_.draw(line, 2, sf::Lines);
}

bool Engine::determineLabelType(unsigned int mask) const
{
    bool result {};

    DrawingBitSet b1 {drawing_}, b2 {mask};

    b1 &= b2;

    for (std::size_t bit {}; bit < b2.size(); ++bit)
        if (b2.test(bit))
            result = (!result != !b1.test(bit));   // Logical XOR

    return result;
}
