
#ifndef PACMANGAME_PACMAN_H
#define PACMANGAME_PACMAN_H

#include "EntityModel.h"

namespace Logic {
    class PacMan : public EntityModel {
    private:
        float x, y;
        float speed = 0.5f;
        int dirX = 0;
        int dirY = 0;

    public:
        PacMan(float startX, float startY) : x(startX), y(startY) {}

        float getX() const override {return x;}
        float getY() const override {return y;}

        void setPos(float newX, float newY) {
            x = newX;
            y = newY;
        }

        void setDirection(int dx, int dy) {
            dirX = dx;
            dirY = dy;
        }

        void update(float deltaTime) {
            x += dirX * speed * deltaTime;
            y += dirY * speed * deltaTime;
        }
    };
}

#endif //PACMANGAME_PACMAN_H
