//
//

#ifndef ENGINE_HPP
#define ENGINE_HPP

#include <bitset>
#include <map>
#include <memory>
#include <string>

#include <SFML/Graphics.hpp>

#include "EntityManager.hpp"

using ActionMap = std::map<std::size_t, std::string>;

class Action;

class Engine
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
    ConfigDetails config_ {};

    sf::RenderWindow window_;

    EntityManager entityManager_;

    ActionMap actionMap_;
    sf::Font font_;
    sf::Text labelText_;

    std::map<int, std::string> atomTypes_;
    std::vector<std::pair<std::shared_ptr<Entity>, std::shared_ptr<Entity>>> bonds_;

    Vec2 mousePos_ {};
    Vec2 boxSize_ {};
    Vec2 maxPos_ {};

    std::string outputFileName_ {"graphene.omd"};

    bool running_ {true};
    bool canRedo_ {false};

    DrawingBitSet drawing_ {0b00001};

    void init(const std::string& config);
    void quit();

    void sUserInput();
    void sDoAction(const Action& action);
    void sGui();
    void sBonding();
    void sPerformSwap();
    void sRender();

    void createGrapheneLattice();
    void calculateBonds(const std::shared_ptr<Entity>& e);
    void writeXYZFile(const std::string& fileName);
    void writeOMDFile(const std::string& fileName);

    bool isMouseWithin(std::shared_ptr<Entity> e) const;
    void drawLine(const Vec2& p1, const Vec2& p2);
    bool determineLabelType(unsigned int mask) const;

    void registerAction(int inputKeyCode, const std::string& actionName) { actionMap_[inputKeyCode] = actionName; }
    bool isRunning() { return running_ && window_.isOpen(); }

public:
    Engine(const std::string& config);

    void run();
};

#endif
