#include "ConcreteFactory.h"
#include "Wall.h"
#include "Coin.h"
#include "PacMan.h"

namespace Representation {
    ConcreteFactory::ConcreteFactory(int width, int height) : camera(width, height) {
        texture.loadFromFile("assets/sprites/sprite.png");

        defineSprites();
    }

    void ConcreteFactory::defineSprites() {
        spriteRects["pacman_closed"] = sf::IntRect(853, 5, 33, 33);

        spriteRects["pacman_right_open"] = sf::IntRect(853, 105, 33, 33);
        spriteRects["pacman_left_open"]  = sf::IntRect(853, 405, 33, 33);
        spriteRects["pacman_up_open"]    = sf::IntRect(853, 554, 33, 33);
        spriteRects["pacman_down_open"]  = sf::IntRect(852, 255, 33, 33);

        // Red (Index 0)
        spriteRects["ghost_0_right"] = sf::IntRect(1, 4, 35, 35);
        spriteRects["ghost_0_left"]  = sf::IntRect(1, 204, 35, 35);

        // Pink (Index 1)
        spriteRects["ghost_1_right"] = sf::IntRect(51, 4, 35, 35);
        spriteRects["ghost_1_left"]  = sf::IntRect(51, 204, 35, 35);

        // Blue (Cyan) (Index 2)
        spriteRects["ghost_2_right"] = sf::IntRect(101, 4, 35, 35);
        spriteRects["ghost_2_left"]  = sf::IntRect(101, 204, 35, 35);

        // Orange (Index 3)
        spriteRects["ghost_3_right"] = sf::IntRect(151, 4, 35, 35);
        spriteRects["ghost_3_left"]  = sf::IntRect(151, 204, 35, 35);

        // Fear Mode
        spriteRects["ghost_scared"] = sf::IntRect(1, 554, 35, 35);

        spriteRects["coin"] = sf::IntRect(411, 313, 16, 16);
        spriteRects["fruit"] = sf::IntRect(601, 200, 33, 42);

        //PACMAN ANIMATION FRAMES
        // RIGHT
        spriteRects["pacman_right_closed"] = sf::IntRect(853, 5, 33, 33);
        spriteRects["pacman_right_half"]   = sf::IntRect(853, 55, 33, 33);
        spriteRects["pacman_right_open"]   = sf::IntRect(853, 105, 33, 33);

        // DOWN
        spriteRects["pacman_down_closed"] = sf::IntRect(852, 155, 33, 33);
        spriteRects["pacman_down_half"]   = sf::IntRect(852, 205, 33, 33);
        spriteRects["pacman_down_open"]   = sf::IntRect(852, 255, 33, 33);

        // LEFT
        spriteRects["pacman_left_closed"] = sf::IntRect(853, 305, 33, 33);
        spriteRects["pacman_left_half"]   = sf::IntRect(853, 355, 33, 33);
        spriteRects["pacman_left_open"]   = sf::IntRect(853, 405, 33, 33);

        // UP
        spriteRects["pacman_up_closed"] = sf::IntRect(853, 454, 33, 33);
        spriteRects["pacman_up_half"]   = sf::IntRect(853, 504, 33, 33);
        spriteRects["pacman_up_open"]   = sf::IntRect(853, 554, 33, 33);

    }

    sf::IntRect ConcreteFactory::getSpriteRect(const std::string &name) const {
            return spriteRects.at(name);
    }

    std::shared_ptr<Logic::Wall> ConcreteFactory::createWall(float x, float y, float width, float height) {
        auto logicWall = std::make_shared<Logic::Wall>(x, y, width, height);

        sf::Vector2f fullSize = camera.getSizeInPixels(width, height);
        sf::Vector2f visualSize = fullSize * 0.9f;

        auto shape = std::make_shared<sf::RectangleShape>(visualSize);
        shape->setFillColor(sf::Color::Blue);

        sf::Vector2f pos = camera.toPixels(x, y);
        shape->setPosition(pos);

        shape->setOrigin(visualSize.x / 2.0f, visualSize.y / 2.0f);

        walls.push_back(shape);
        return logicWall;
    }

    std::shared_ptr<Logic::PacMan> ConcreteFactory::createPacMan(float x, float y, float width, float height) {
        auto logicPacMan = std::make_shared<Logic::PacMan>(x, y, width, height, x, y);

        auto right = getAnimationFrames("right");
        auto left  = getAnimationFrames("left");
        auto up    = getAnimationFrames("up");
        auto down  = getAnimationFrames("down");

        pacmanView = std::make_shared<PacManView>(logicPacMan, camera, texture, right, left, up, down);
        logicPacMan->addObserver(pacmanView);

        return logicPacMan;
    }

    std::shared_ptr<Logic::Coin> ConcreteFactory::createCoin(float x, float y) {
        auto logicCoin = std::make_shared<Logic::Coin>(x, y);

        float logicRadius = 0.01f;
        sf::Vector2f pixelSize = camera.getSizeInPixels(logicRadius * 2.0f, logicRadius * 2.0f);

        auto shape = std::make_shared<sf::CircleShape>(pixelSize.x / 2.0f);
        shape->setFillColor(sf::Color::White);

        sf::Vector2f pos = camera.toPixels(x, y);
        shape->setPosition(pos);
        shape->setOrigin(pixelSize.x / 2.0f, pixelSize.x / 2.0f);

        coinSprites.push_back(shape);

        return logicCoin;
    }

    std::shared_ptr<Logic::Ghost> ConcreteFactory::createGhost(float x, float y, float width, float height, int index) {
        std::shared_ptr<Logic::Ghost> logicGhost;

        // Create the appropriate ghost subclass
        switch(index % 4) {
            case 0:
                logicGhost = std::make_shared<Logic::RedGhost>(x, y, width, height);
                break;
            case 1:
                logicGhost = std::make_shared<Logic::PinkGhost>(x, y, width, height);
                break;
            case 2:
                logicGhost = std::make_shared<Logic::BlueGhost>(x, y, width, height);
                break;
            case 3:
                logicGhost = std::make_shared<Logic::OrangeGhost>(x, y, width, height);
                break;
        }

        std::string name = "ghost_" + std::to_string(index % 4) + "_right";
        sf::IntRect normalRect = getSpriteRect(name);
        sf::IntRect scaredRect = getSpriteRect("ghost_scared");

        auto view = std::make_shared<GhostView>(logicGhost, camera, texture, normalRect, scaredRect);
        logicGhost->addObserver(view);
        ghostviews.push_back(view);

        return logicGhost;
    }

    const std::vector<std::shared_ptr<GhostView>> &ConcreteFactory::getGhostviews() const {
        return ghostviews;
    }

    std::shared_ptr<Logic::Fruit> ConcreteFactory::createFruit(float x, float y) {
        auto logicFruit = std::make_shared<Logic::Fruit>(x, y);
        float logicRadius = 0.02f;
        sf::Vector2f pixelSize = camera.getSizeInPixels(logicRadius * 2, logicRadius * 2);

        auto shape = std::make_shared<sf::CircleShape>(pixelSize.x / 2.0f);
        shape->setFillColor(sf::Color(255, 182, 147));

        sf::Vector2f pos = camera.toPixels(x, y);
        shape->setPosition(pos);
        shape->setOrigin(pixelSize.x / 2.0f, pixelSize.x / 2.0f);

        fruitSprites.push_back(shape);
        return logicFruit;
    }

    std::vector<sf::IntRect> ConcreteFactory::getAnimationFrames(const std::string& direction) const {
        std::vector<sf::IntRect> frames;
        std::string base = "pacman_" + direction;

        frames.push_back(getSpriteRect(base + "_closed"));
        frames.push_back(getSpriteRect(base + "_half"));
        frames.push_back(getSpriteRect(base + "_open"));
        frames.push_back(getSpriteRect(base + "_half"));

        return frames;
    }

}
