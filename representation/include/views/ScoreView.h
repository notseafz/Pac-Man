

#ifndef PACMANGAME_SCOREVIEW_H
#define PACMANGAME_SCOREVIEW_H
#include "EntityView.h"
#include "core/Observer.h"
#include "core/Score.h"
#include <SFML/Graphics.hpp>
#include <iostream>

namespace Representation {
/**
 * @brief UI component for displaying the score.
 *
 * Observes the Score singleton to update text dynamically.
 */
class ScoreView : public Logic::Observer {
private:
    sf::Text scoretext;
    sf::Font font;
    sf::Text highScoreText;

public:
    ScoreView() {
        font.loadFromFile("assets/fonts/emulogic.ttf");

        // Current Score
        scoretext.setFont(font);
        scoretext.setCharacterSize(20);
        scoretext.setFillColor(sf::Color::Yellow);
        scoretext.setPosition(10.f, 565.f);

        update();
    }

    void update() override {
        int score = Logic::Score::getInstance().getScore();
        scoretext.setString("SCORE:" + std::to_string(score));
    }

    void draw(sf::RenderWindow& window) { window.draw(scoretext); }

    virtual ~ScoreView() = default;
};
} // namespace Representation
#endif // PACMANGAME_SCOREVIEW_H
