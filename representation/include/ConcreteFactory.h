
#ifndef PACMANGAME_CONCRETEFACTORY_H
#define PACMANGAME_CONCRETEFACTORY_H

#include "AbstractFactory.h"
#include "Camera.h"
#include "Ghost.h"
#include "GhostView.h"
#include "PacMan.h"
#include "PacmanView.h"
#include "entities/Fruit.h"
#include <SFML/Graphics.hpp>
#include <vector>

namespace Representation {
class ConcreteFactory : public Logic::AbstractFactory {
private:
    std::vector<std::shared_ptr<sf::RectangleShape>> walls;
    std::shared_ptr<sf::CircleShape> pacmanSprite;
    std::shared_ptr<PacManView> pacmanView;
    std::vector<std::shared_ptr<sf::CircleShape>> coinSprites;
    std::vector<std::shared_ptr<GhostView>> ghostviews;
    std::vector<std::shared_ptr<sf::CircleShape>> fruitSprites;

    sf::Texture texture;
    std::map<std::string, sf::IntRect> spriteRects;
    void defineSprites();

public:
    ConcreteFactory(int width, int height);
    sf::IntRect getSpriteRect(const std::string& name) const;
    std::vector<sf::IntRect> getAnimationFrames(const std::string& baseName) const;

    std::shared_ptr<Logic::Wall> createWall(float x, float y, float width, float height) override;
    std::shared_ptr<Logic::PacMan> createPacMan(float x, float y, float widht, float height) override;
    std::shared_ptr<Logic::Coin> createCoin(float x, float y) override;
    std::shared_ptr<Logic::Ghost> createGhost(float x, float y, float width, float height, int index) override;

    std::shared_ptr<sf::CircleShape> getPacManSprite() { return pacmanSprite; }
    std::shared_ptr<PacManView> getPacManView() { return pacmanView; }
    const std::vector<std::shared_ptr<sf::CircleShape>>& getCoinSprites() const { return coinSprites; }
    const std::vector<std::shared_ptr<GhostView>>& getGhostViews() const { return ghostviews; }

    std::shared_ptr<Logic::Fruit> createFruit(float x, float y) override;
    const std::vector<std::shared_ptr<sf::CircleShape>>& getFruitSprites() const { return fruitSprites; }
    const std::vector<std::shared_ptr<sf::RectangleShape>>& getWallSprites() const { return walls; }
    const std::vector<std::shared_ptr<GhostView>>& getGhostviews() const;

    Camera camera;
};
} // namespace Representation

#endif // PACMANGAME_CONCRETEFACTORY_H
