

#ifndef PACMANGAME_HIGHSCORE_H
#define PACMANGAME_HIGHSCORE_H


#include <string>
#include <fstream>
#include <iostream>

namespace Logic {
    class HighScore {
    public:
        static int load() {
            std::ifstream file("assets/highscores.txt");
            int score = 0;
            if (file.is_open()) {
                file >> score;
                file.close();
            } else {
                save(0);
            }
            return score;
        }

        static void save(int score) {
            std::ofstream file("assets/highscores.txt");
            if (file.is_open()) {
                file << score;
                file.close();
            } else {
                std::cerr << "[Error] Could not save high score!" << std::endl;
            }
        }
    };
}


#endif //PACMANGAME_HIGHSCORE_H
