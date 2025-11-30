#include "ConcreteFactory.h"
#include "Wall.h"

namespace Representation {
    std::shared_ptr<Logic::Wall> ConcreteFactory::createWall(float x, float y, float width, float height) {
        auto logicWall = std::make_shared<Logic::Wall>(x, y);

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

    std::shared_ptr<Logic::PacMan> ConcreteFactory::createPacMan(float x, float y) {
        auto logicPacMan = std::make_shared<Logic::PacMan>(x, y);

        float radiusLogic = 0.03f;
        sf::Vector2f pixelSize = camera.getSizeInPixels(radiusLogic * 2.0f, radiusLogic * 2.0f);

        pacmanSprite = std::make_shared<sf::CircleShape>(pixelSize.x / 2.0f);
        pacmanSprite->setFillColor(sf::Color::Yellow);

        sf::Vector2f pos = camera.toPixels(x, y);
        pacmanSprite->setPosition(pos);

        pacmanSprite->setOrigin(pixelSize.x / 2.0f, pixelSize.x / 2.0f);

        return logicPacMan;
    }

}