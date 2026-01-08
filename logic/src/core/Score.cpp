
#include "core/Score.h"
#include "core/HighScore.h"

namespace Logic {
    Score *Score::instance = nullptr;

    Score &Score::getInstance() {
        if (!instance) instance = new Score();
        return *instance;
    }
    Score::Score() {
        HighScore::loadHighest();
    }

    void Score::addScore(int points) {
        current += points;

        // If we beat the high score, update it immediately
        if (current > highScore) {
            highScore = current;
            HighScore::save(highScore); // <--- SAVE TO FILE
        }

        notify();
    }

    int Score::getScore() const {
        return current;
    }

    void Score::resetScore() {
        current = 0;
        timeSinceLastCoin = 0.0f;
        decayTimer = 0.0f;
        notify();
    }


    void Score::save() {
        HighScore::save(current);

    }

    void Score::addCoinScore() {
        int points = 10; // Base value

        if (timeSinceLastCoin < 0.5f) points += 40;
        else if (timeSinceLastCoin < 1.0f) points += 20;
        else if (timeSinceLastCoin < 2.0f) points += 10;

        current += points;
        timeSinceLastCoin = 0.0f;
        notify();

    }

    void Score::update(float dt) {
        timeSinceLastCoin += dt;
        decayTimer += dt;

        if (decayTimer >= 1.0f) {
            decayTimer = 0.0f;
            if (current > 0) {
                current -= 10;
                if (current < 0) current = 0;
                notify();
            }
        }
    }


}