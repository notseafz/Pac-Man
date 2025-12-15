#include "ConcreteFactory.h"
#include "Wall.h"
#include "Coin.h"
#include "PacMan.h"

namespace Representation {
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

        pacmanView = std::make_shared<PacManView>(logicPacMan, camera);
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
        auto logicGhost = std::make_shared<Logic::Ghost>(x, y, width, height, index);

        // Pick Color based on Index
        sf::Color color;
        switch (index % 4) {
            case 0: color = sf::Color::Red; break;
            case 1: color = sf::Color(255, 182, 255); break; // Pink
            case 2: color = sf::Color::Cyan; break;          // Blue
            case 3: color = sf::Color(255, 182, 85); break;  // Orange
        }

        // Pass color to View
        auto view = std::make_shared<GhostView>(logicGhost, camera, color);

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

}