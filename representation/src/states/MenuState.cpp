#include "states/MenuState.h"
#include "states/LevelState.h"

namespace Representation {
    MenuState::MenuState(StateManager& sm, sf::RenderWindow& win)
            : stateManager(sm), window(win) {}

    void MenuState::init() {
        if (!font.loadFromFile("assets/fonts/emulogic.ttf")) return;

        text.setFont(font);
        text.setString("PAC-MAN\n\nPress ENTER to Play");
        text.setCharacterSize(30);
        text.setFillColor(sf::Color::Yellow);
        text.setPosition(100, 250);
        //TODO: center text properly
    }

    void MenuState::handleInput() {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) window.close();
            if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Enter) {
                // Switch to Level State (Replace Menu)
                stateManager.addState(std::make_unique<LevelState>(stateManager, window), true);
            }
        }
    }

    void MenuState::draw() {
        window.draw(text);
    }
}