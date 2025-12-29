
#include "core/Score.h"

namespace Logic {
    Score *Score::instance = nullptr;

    Score &Score::getInstance() {
        if (!instance) instance = new Score();
        return *instance;
    }

    void Score::addScore(int points) {
        current += points;
        if (current > highscore) {
            highscore = current;
            HighScore::save(highscore);
        }
        notify();
    }

    int Score::getScore() const {
        return current;
    }

    void Score::resetScore() {
        current = 0;
        highscore = HighScore::load();
        notify();
    }

    int Score::getHighScore() {
        return highscore;
    }
}