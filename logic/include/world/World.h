#pragma once
#include "AbstractFactory.h"
#include "entities/EntityModel.h"
#include "entities/Wall.h"
#include <memory>
#include <vector>

namespace Logic {
class World {
private:
    std::shared_ptr<AbstractFactory> factory;
    std::vector<std::shared_ptr<EntityModel>> entities;
    std::shared_ptr<PacMan> pacman;
    std::vector<std::shared_ptr<Wall>> walls;
    std::vector<std::shared_ptr<Coin>> coins;
    std::vector<std::shared_ptr<Ghost>> ghosts;
    std::vector<std::shared_ptr<Fruit>> fruits;

    int currentLevel = 1;
    float difficultyMultiplier = 1.0f;

public:
    World(std::shared_ptr<AbstractFactory> factory);
    std::shared_ptr<PacMan> getPacMan() { return pacman; }
    const std::vector<std::shared_ptr<Coin>>& getCoins() const { return coins; }
    const std::vector<std::shared_ptr<Fruit>>& getFruits() const { return fruits; }
    void update();

    void nextLevel();
    int getLevel() const { return currentLevel; }
};
} // namespace Logic