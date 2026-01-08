
#ifndef PACMANGAME_SCORE_H
#define PACMANGAME_SCORE_H

#include "Subject.h"
#include "HighScore.h"

namespace Logic {
    class Score : public Subject {
    private:
        static Score* instance;
        int current = 0;
        int highScore;

        float timeSinceLastCoin = 0.0f;
        float decayTimer = 0.0f;

    public:
        Score();
        static Score& getInstance();

        Score(const Score&) = delete;
        void operator = (const Score&) = delete;

        void addScore(int points);
        void addCoinScore();
        void update(float dt);
        void save();
        int getScore() const;
        void resetScore();

        int getHighScore();


    };
}
#endif //PACMANGAME_SCORE_H
