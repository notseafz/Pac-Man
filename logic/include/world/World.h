#pragma once
#include <vector>
#include <memory>
#include "AbstractFactory.h"
#include "entities/EntityModel.h"
#include "entities/Wall.h"

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
    public:
        World(std::shared_ptr<AbstractFactory> factory);
        std::shared_ptr<PacMan> getPacMan() { return pacman;}
        const std::vector<std::shared_ptr<Coin>>& getCoins() const {return coins;}
        const std::vector<std::shared_ptr<Fruit>>& getFruits() const { return fruits; }
        void update();
    };
}