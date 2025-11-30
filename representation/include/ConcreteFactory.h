
#ifndef PACMANGAME_CONCRETEFACTORY_H
#define PACMANGAME_CONCRETEFACTORY_H

#include "AbstractFactory.h"
#include <vector>
#include <SFML/Graphics.hpp>
#include "Camera.h"

namespace Representation {
    class ConcreteFactory : public Logic::AbstractFactory {
    private:
        std::vector<std::shared_ptr<sf::RectangleShape>> walls;
        Camera camera;

    public:
        std::shared_ptr<Logic::Wall> createWall(float x, float y, float width, float height) override;

        ConcreteFactory(int width, int height) : camera(width, height) {}

        const std::vector<std::shared_ptr<sf::RectangleShape>>& getWallSprites() const {
            return walls;
        }
    };
}

#endif //PACMANGAME_CONCRETEFACTORY_H
