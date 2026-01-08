#pragma once
#include "AbstractFactory.h"
#include "entities/EntityModel.h"
#include "entities/Wall.h"
#include <memory>
#include <vector>

namespace Logic {
/**
 * @brief The main Controller for the game logic.
 * Manages the map, entities, collision detection, and level progression.
 */
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

    /**
     * @brief Advances the game simulation by one tick.
     * Updates movement, checks collisions, and manages game rules.
     */
    void update();

    // Resets the map entities and increases difficulty for the next level.
    void nextLevel();
    int getLevel() const { return currentLevel; }
};
} // namespace Logic