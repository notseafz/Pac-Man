#include "ConcreteFactory.h"
#include "Wall.h"

namespace Representation {
    std::shared_ptr<Logic::Wall> ConcreteFactory::createWall(float x, float y, float width, float height) {
        auto logicWall = std::make_shared<Logic::Wall>(x, y);

        sf::Vector2f pixelSize = camera.getSizeInPixels(width, height);

        auto shape = std::make_shared<sf::RectangleShape>(pixelSize);
        shape->setFillColor(sf::Color::Blue);

        sf::Vector2f pos = camera.toPixels(x, y);
        shape->setPosition(pos);

        shape->setOrigin(pixelSize.x / 2.0f, pixelSize.y / 2.0f);

        walls.push_back(shape);
        return logicWall;
    }

}