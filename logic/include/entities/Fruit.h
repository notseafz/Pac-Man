//
// Created by meiya on 15/12/2025.
//

#ifndef PACMANGAME_FRUIT_H
#define PACMANGAME_FRUIT_H
#include "Collectable.h"

namespace Logic {
    class Fruit : public Collectable {
    public:
        Fruit(float px, float py) : Collectable(px, py, 50) {
            width = 0.03f;
            height = 0.03f;
        }
    };
}
#endif //PACMANGAME_FRUIT_H
