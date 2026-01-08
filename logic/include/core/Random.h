//
// Created by meiya on 06/01/2026.
//

#ifndef PACMANGAME_RANDOM_H
#define PACMANGAME_RANDOM_H

#include <random>

namespace Logic {
class Random {
private:
    std::mt19937 mt; // The Mersenne Twister engine

    // Private Constructor (Singleton)
    Random() {
        std::random_device rd;
        mt.seed(rd());
    }

public:
    // Singleton Access
    static Random& getInstance() {
        static Random instance;
        return instance;
    }

    // Delete copy/move
    Random(const Random&) = delete;
    void operator=(const Random&) = delete;

    // Get random integer [min, max] (Inclusive)
    int getInt(int min, int max) {
        std::uniform_int_distribution<int> dist(min, max);
        return dist(mt);
    }

    // Get random float [min, max]
    float getFloat(float min, float max) {
        std::uniform_real_distribution<float> dist(min, max);
        return dist(mt);
    }
};
} // namespace Logic

#endif // PACMANGAME_RANDOM_H
