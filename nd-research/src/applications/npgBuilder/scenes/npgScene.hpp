// Copyright (c) 2019-2024 Cody R. Drisko. All rights reserved.
// Licensed under the MIT License. See the LICENSE file in the project root for more information.
//
// Name: npgScene.hpp
// Author: crdrisko
// Date: 11/13/2024-06:07:07
// Description:

#ifndef ND_GRAD_ND_RESEARCH_SRC_APPLICATIONS_NPGBUILDER_SCENES_NPGSCENE_HPP
#define ND_GRAD_ND_RESEARCH_SRC_APPLICATIONS_NPGBUILDER_SCENES_NPGSCENE_HPP

#include <memory>
#include <string>

#include <SFML/Graphics.hpp>
#include <dryphys/math.hpp>
#include <engine2d/action.hpp>
#include <engine2d/engine.hpp>
#include <engine2d/scene.hpp>

#include "npgBuilder/forwardDeclare.hpp"

namespace NPGBuilder
{
    class NPGScene : public Engine2D::Scene
    {
        struct ConfigDetails
        {
            std::size_t worldScale {30};

            std::size_t desiredBoxX {40}, desiredBoxY {40};

            float hydrogenBondLength {1.08f}, carbonBondLength {1.37f};
            float hydrogenAtomRadius {5.0f}, carbonAtomRadius {10.0f};
        };

        enum DrawingFlags
        {
            BEGININDEX = 0,
            BONDS      = BEGININDEX,
            LABELS,
            ATOMTYPES,
            BONDORDER,
            SCALE,
            ENDINDEX
        };

        using DrawingBitSet = std::bitset<ENDINDEX - BEGININDEX>;

    private:
        ConcreteEntityPtr player_;
        ConcreteEntityManager entityManager_;
        ConfigDetails config_ {};

        std::map<int, std::string> atomTypes_;
        std::vector<std::pair<ConcreteEntityPtr, ConcreteEntityPtr>> bonds_;

        float width_ {}, height_ {};
        const float gridSize_ {64};

        sf::Font font_;
        sf::Text labelText_;

        DryPhys::Vector3D mousePos_;
        DryPhys::Vector3D boxSize_ {};
        DryPhys::Vector3D maxPos_ {};

        std::string outputFileName_ {"graphene.omd"};

        bool running_ {true};
        bool canRedo_ {false};

        DrawingBitSet drawing_ {0b00001};

        void init(const std::string& config);
        void loadLevel(const std::string& filename);
        void update() override;
        void postUpdate() override;
        void doActionImpl(const Engine2D::Action& action) override;
        void render() override;
        void onEnd() override;

        // Systems
        void sGui();
        void sBonding();
        void sPerformSwap();

        void createGrapheneLattice();
        void calculateBonds(ConcreteEntityPtr entity);
        void writeXYZFile(const std::string& fileName);
        void writeOMDFile(const std::string& fileName);

        bool isMouseWithin(ConcreteEntityPtr entity) const;
        bool determineLabelType(unsigned int mask) const;

    public:
        NPGScene(Engine2D::Engine* gameEngine, const std::string& config);
    };
}   // namespace NPGBuilder

#endif
