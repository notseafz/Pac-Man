
#ifndef PACMANGAME_SCORE_H
#define PACMANGAME_SCORE_H

#include "HighScore.h"
#include "Subject.h"

namespace Logic {
/**
     * @brief Singleton class to manage the player's score.
     * Handles current score, high score persistence, and combo logic.
 */
class Score : public Subject {
private:
    static Score* instance;
    int current = 0;
    int highScore;

    float timeSinceLastCoin = 0.0f;
    float decayTimer = 0.0f;

public:
    Score();
    // returns the global instance of the Score system
    static Score& getInstance();

    Score(const Score&) = delete;
    void operator=(const Score&) = delete;

    void addScore(int points);
    void addCoinScore();
    void update(float dt);
    void save();
    int getScore() const;
    void resetScore();

};
} // namespace Logic
#endif // PACMANGAME_SCORE_H
