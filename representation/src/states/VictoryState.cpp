#include "states/VictoryState.h"
#include "states/MenuState.h"

namespace Representation {
    VictoryState::VictoryState(StateManager& sm, sf::RenderWindow& win)
            : stateManager(sm), window(win) {}

    void VictoryState::init() {
        if (!font.loadFromFile("assets/fonts/emulogic.ttf")) return;
        text.setFont(font);
        text.setString("VICTORY!\n\nAll Coins Collected!\nPress ENTER to Return");
        text.setCharacterSize(30);
        text.setFillColor(sf::Color::Green);
        text.setPosition(200, 250);
    }

    void VictoryState::handleInput() {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) window.close();
            if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Enter) {
                // Return to Menu
                stateManager.addState(std::make_unique<MenuState>(stateManager, window), true);
            }
        }
    }

    void VictoryState::draw() {
        window.draw(text);
    }
}