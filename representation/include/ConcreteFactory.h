
#ifndef PACMANGAME_CONCRETEFACTORY_H
#define PACMANGAME_CONCRETEFACTORY_H

#include "AbstractFactory.h"
#include <vector>
#include <SFML/Graphics.hpp>
#include "Camera.h"
#include "PacMan.h"

namespace Representation {
    class ConcreteFactory : public Logic::AbstractFactory {
    private:
        std::vector<std::shared_ptr<sf::RectangleShape>> walls;
        std::shared_ptr<sf::CircleShape> pacmanSprite;

    public:
        std::shared_ptr<Logic::Wall> createWall(float x, float y, float width, float height) override;
        std::shared_ptr<Logic::PacMan> createPacMan(float x, float y) override;

        std::shared_ptr<sf::CircleShape> getPacManSprite() { return pacmanSprite; }

        ConcreteFactory(int width, int height) : camera(width, height) {}

        const std::vector<std::shared_ptr<sf::RectangleShape>>& getWallSprites() const {
            return walls;
        }

        Camera camera;
    };
}

#endif //PACMANGAME_CONCRETEFACTORY_H
