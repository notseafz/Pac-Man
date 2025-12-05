
#ifndef PACMANGAME_ABSTRACTFACTORY_H
#define PACMANGAME_ABSTRACTFACTORY_H

#include <memory>

namespace Logic {
    class Wall;
    class PacMan;
    class Coin;

    class AbstractFactory {
    public:
        virtual ~AbstractFactory() = default;
        virtual std::shared_ptr<Wall> createWall(float x, float y, float width, float height) = 0;
        virtual std::shared_ptr<PacMan> createPacMan(float x, float y, float width, float height) = 0;
        virtual std::shared_ptr<Coin> createCoin(float x, float y) = 0;
    };
}

#endif //PACMANGAME_ABSTRACTFACTORY_H
