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
    public:
        World(std::shared_ptr<AbstractFactory> factory);
        std::shared_ptr<PacMan> getPacMan() { return pacman;}
        void update();
    };
}