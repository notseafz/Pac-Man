//
// Created by meiya on 08/01/2026.
//

#ifndef PACMANGAME_LIVESVIEW_H
#define PACMANGAME_LIVESVIEW_H

#include "EntityView.h"
#include "entities/PacMan.h"
#include <SFML/Graphics.hpp>
#include <iostream>
#include <memory>

namespace Representation {
class LivesView : public Logic::Observer {
private:
    sf::Text text;
    sf::Font font;
    std::shared_ptr<Logic::PacMan> pacman;

public:
    LivesView(std::shared_ptr<Logic::PacMan> p) : pacman(p) {
        if (!font.loadFromFile("assets/fonts/emulogic.ttf")) {
            std::cerr << "Error loading font" << std::endl;
        }

        text.setFont(font);
        text.setCharacterSize(20);
        text.setFillColor(sf::Color::Yellow);

        text.setPosition(750.f, 565.f);

        update();
    }

    void update() override {
        if (pacman) {
            text.setString("#" + std::to_string(pacman->getLives()));
        }
    }

    void draw(sf::RenderWindow& window) { window.draw(text); }
};
} // namespace Representation

#endif // PACMANGAME_LIVESVIEW_H
