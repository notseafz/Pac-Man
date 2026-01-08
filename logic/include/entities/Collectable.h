//
// Created by meiya on 05/12/2025.
//

#ifndef PACMANGAME_COLLECTABLE_H
#define PACMANGAME_COLLECTABLE_H
#include "EntityModel.h"

namespace Logic {
class Collectable : public EntityModel {
protected:
    float x, y;
    float width = 0.02f;
    float height = 0.02f;
    int scoreValue;
    bool isCollected = false;

public:
    Collectable(float px, float py, int points) : x(px), y(py), scoreValue(points) {}

    float getX() const override { return x; }
    float getY() const override { return y; }

    bool getIsCollected() const { return isCollected; }
    int getScoreValue() const { return scoreValue; }

    void collect() {
        isCollected = true;
        notify();
    }

    void reset() { isCollected = false; }
};
} // namespace Logic

#endif // PACMANGAME_COLLECTABLE_H
