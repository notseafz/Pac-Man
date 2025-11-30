

#ifndef PACMANGAME_WALL_H
#define PACMANGAME_WALL_H

#include "EntityModel.h"

namespace Logic {
    class Wall: public EntityModel {
    private:
        float x;
        float y;

    public:
        Wall(float px, float py) : x(px), y(py) {}
        float getX() const override {return x;}
        float getY() const override {return y;}
    };
}

#endif //PACMANGAME_WALL_H
