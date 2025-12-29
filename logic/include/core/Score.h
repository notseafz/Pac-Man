
#ifndef PACMANGAME_SCORE_H
#define PACMANGAME_SCORE_H

#include "Subject.h"
#include "HighScore.h"

namespace Logic {
    class Score : public Subject {
    private:
        static Score* instance;
        int current = 0;
        int highscore = 0;

        Score() {
            highscore = HighScore::load();
        }

    public:
        static Score& getInstance();

        Score(const Score&) = delete;
        void operator = (const Score&) = delete;

        void addScore(int points);
        int getScore() const;
        void resetScore();

        int getHighScore();
    };
}
#endif //PACMANGAME_SCORE_H
