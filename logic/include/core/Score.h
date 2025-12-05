
#ifndef PACMANGAME_SCORE_H
#define PACMANGAME_SCORE_H

#include "Subject.h"

namespace Logic {
    class Score : public Subject {
    private:
        static Score* instance;
        int current = 0;

        Score() = default;

    public:
        static Score& getInstance();

        void addScore(int points);
        int getScore() const;
    };
}
#endif //PACMANGAME_SCORE_H
