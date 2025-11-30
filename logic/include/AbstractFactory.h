
#ifndef PACMANGAME_ABSTRACTFACTORY_H
#define PACMANGAME_ABSTRACTFACTORY_H

#include <memory>

namespace Logic {
    class Wall;

    class AbstractFactory {
    public:
        virtual ~AbstractFactory() = default;
        virtual std::shared_ptr<Wall> createWall(float x, float y, float width, float height) = 0;
    };
}

#endif //PACMANGAME_ABSTRACTFACTORY_H
