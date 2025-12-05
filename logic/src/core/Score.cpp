
#include "core/Score.h"

namespace Logic {
    Score *Score::instance = nullptr;

    Score &Score::getInstance() {
        if (!instance) instance = new Score();
        return *instance;
    }

    void Score::addScore(int points) {
        current += points;
        notify();
    }

    int Score::getScore() const {
        return current;
    }
}