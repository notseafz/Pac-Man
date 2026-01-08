

#ifndef PACMANGAME_HIGHSCORE_H
#define PACMANGAME_HIGHSCORE_H

#include <fstream>
#include <iostream>
#include <string>

namespace Logic {
class HighScore {
public:
    static std::vector<int> load() {
        std::ifstream file("assets/highscores.txt");
        std::vector<int> scores;
        int val;

        if (file.is_open()) {
            while (file >> val) {
                scores.push_back(val);
            }
        }
        file.close();

        std::sort(scores.rbegin(), scores.rend());
        if (scores.size() > 5)
            scores.resize(5);

        return scores;
    }

    static void save(int score) {
        auto scores = load();
        scores.push_back(score);

        std::sort(scores.rbegin(), scores.rend());
        if (scores.size() > 5)
            scores.resize(5);

        std::ofstream file("assets/highscores.txt");
        if (file.is_open()) {
            for (int s : scores) {
                file << s << "\n";
            }
            file.close();
        }
    }

    static int loadHighest() {
        auto scores = load();
        if (scores.empty())
            return 0;
        return scores[0];
    }
};
} // namespace Logic

#endif // PACMANGAME_HIGHSCORE_H
