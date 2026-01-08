//
// Created by meiya on 05/12/2025.
//

#ifndef PACMANGAME_COIN_H
#define PACMANGAME_COIN_H
#include "Collectable.h"

namespace Logic {
/**
     * @brief Represents a pick-up item.
     *
     * Stores score value and collection state.
 */
class Coin : public Collectable {
public:
    Coin(float px, float py) : Collectable(px, py, 2) {}
};
} // namespace Logic

#endif // PACMANGAME_COIN_H
