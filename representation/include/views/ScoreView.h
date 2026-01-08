

#ifndef PACMANGAME_SCOREVIEW_H
#define PACMANGAME_SCOREVIEW_H
#include "EntityView.h"
#include "core/Score.h"
#include "core/Observer.h"
#include <SFML/Graphics.hpp>
#include <iostream>

namespace Representation {
    class ScoreView : public Logic::Observer {
    private:
        sf::Text scoretext;
        sf::Font font;
        sf::Text highScoreText;

    public:
        ScoreView() {
            font.loadFromFile("assets/fonts/emulogic.ttf");

            //Current Score
            scoretext.setFont(font);
            scoretext.setCharacterSize(20);
            scoretext.setFillColor(sf::Color::White);
            scoretext.setPosition(10.f, 565.f);

            // High Score
            highScoreText.setFont(font);
            highScoreText.setCharacterSize(20);
            highScoreText.setFillColor(sf::Color::White);
            highScoreText.setPosition(250.f, 10.f);

            update();
        }

        void update() override {
            int score = Logic::Score::getInstance().getScore();
            scoretext.setString("SCORE: " + std::to_string(score));
        }

        void draw(sf::RenderWindow& window) {
            window.draw(scoretext);
        }

        virtual ~ScoreView() = default;

    };
}
#endif //PACMANGAME_SCOREVIEW_H
