

#ifndef PACMANGAME_WALL_H
#define PACMANGAME_WALL_H

#include "EntityModel.h"

namespace Logic {
class Wall : public EntityModel {
private:
    float x;
    float y;
    float width, height;

public:
    Wall(float px, float py, float w, float h) : x(px), y(py), width(w), height(h) {}

    float getX() const override { return x; }
    float getY() const override { return y; }

    float getWidth() const { return width; }
    float getHeight() const { return height; }
};
} // namespace Logic

#endif // PACMANGAME_WALL_H
