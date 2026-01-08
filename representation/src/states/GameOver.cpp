
#include "states/GameOver.h"
#include "states/MenuState.h"
#include "Score.h"
#include <iostream>

namespace Representation {
    GameOver::GameOver(StateManager& sm, sf::RenderWindow& win)
            : stateManager(sm), window(win) {}

    void GameOver::init() {
        Logic::Score::getInstance().save();
        if (!font.loadFromFile("assets/fonts/emulogic.ttf")) return;
        text.setFont(font);
        text.setString("GAME OVER\n\nPress ENTER to Menu");
        text.setCharacterSize(20);
        text.setFillColor(sf::Color::Red);
        text.setPosition(200, 250);
    }

    void GameOver::handleInput() {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) window.close();
            if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Enter) {
                stateManager.addState(std::make_unique<MenuState>(stateManager, window), true);
            }
        }
    }
    void GameOver::draw() { window.draw(text); }
}