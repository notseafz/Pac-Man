

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
        sf::Text text;
        sf::Font font;

    public:
        ScoreView() {
            font.loadFromFile("assets/fonts/emulogic.ttf");
            text.setFont(font);
            text.setCharacterSize(20);
            text.setFillColor(sf::Color::Yellow);
            text.setPosition(10.f, 565.f);
            text.setString("Score: 0");
        }

        void update() override {
            int score = Logic::Score::getInstance().getScore();
            text.setString("Score: " + std::to_string(score));
        }

        void draw(sf::RenderWindow& window) {
            window.draw(text);
        }

    };
}
#endif //PACMANGAME_SCOREVIEW_H
