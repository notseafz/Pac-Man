//
// Created by meiya on 05/12/2025.
//

#ifndef PACMANGAME_COIN_H
#define PACMANGAME_COIN_H
#include "Collectable.h"

namespace Logic {
class Coin : public Collectable {
public:
    Coin(float px, float py) : Collectable(px, py, 2) {}
};
} // namespace Logic

#endif // PACMANGAME_COIN_H
