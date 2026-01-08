#include "states/VictoryState.h"
#include "states/MenuState.h"

namespace Representation {
VictoryState::VictoryState(StateManager& sm, sf::RenderWindow& win, int i) : stateManager(sm), window(win) {}

void VictoryState::init() {
    if (!font.loadFromFile("assets/fonts/emulogic.ttf"))
        return;

    float centerX = window.getSize().x / 2.0f;
    float centerY = window.getSize().y / 2.0f;

    // level cleared text
    levelText.setFont(font);
    levelText.setString("LEVEL " + std::to_string(levelIndex) + " CLEARED!");
    levelText.setCharacterSize(20);
    levelText.setFillColor(sf::Color::Green);

    sf::FloatRect rect1 = levelText.getLocalBounds();
    levelText.setOrigin(rect1.left + rect1.width / 2.0f, rect1.top + rect1.height / 2.0f);

    levelText.setPosition(centerX, centerY - 25.0f);
    pressText.setFont(font);
    pressText.setString("PRESS ENTER TO CONTINUE");
    pressText.setCharacterSize(15);
    pressText.setFillColor(sf::Color::White);

    sf::FloatRect rect2 = pressText.getLocalBounds();
    pressText.setOrigin(rect2.left + rect2.width / 2.0f, rect2.top + rect2.height / 2.0f);

    pressText.setPosition(centerX, centerY + 25.0f);
}

void VictoryState::handleInput() {
    sf::Event event;
    while (window.pollEvent(event)) {
        if (event.type == sf::Event::Closed)
            window.close();
        if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Enter) {
            stateManager.popState();
        }
    }
}

void VictoryState::draw() {
    window.draw(levelText);
    window.draw(pressText);
}
} // namespace Representation