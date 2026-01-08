#include "states/MenuState.h"
#include "core/HighScore.h"
#include "states/LevelState.h"

namespace Representation {
MenuState::MenuState(StateManager& sm, sf::RenderWindow& win) : stateManager(sm), window(win) {}

void MenuState::init() {
    if (!font.loadFromFile("assets/fonts/emulogic.ttf"))
        return;

    float windowCenter = window.getSize().x / 2.0f;

    // 1. TITLE ("PAC-MAN")
    title.setFont(font);
    title.setString("PAC-MAN");
    title.setCharacterSize(40);
    title.setFillColor(sf::Color::Yellow);

    sf::FloatRect titleRect = title.getLocalBounds();
    title.setOrigin(titleRect.left + titleRect.width / 2.0f, titleRect.top + titleRect.height / 2.0f);
    // Changed Y from 100 to 120
    title.setPosition(windowCenter, 120.0f);

    // 2. INSTRUCTION ("PRESS ENTER TO PLAY")
    instruction.setFont(font);
    instruction.setString("PRESS ENTER TO PLAY");
    instruction.setCharacterSize(15);
    instruction.setFillColor(sf::Color::White);

    sf::FloatRect instRect = instruction.getLocalBounds();
    instruction.setOrigin(instRect.left + instRect.width / 2.0f, instRect.top + instRect.height / 2.0f);
    // Changed Y from 200 to 180 (Closer to title)
    instruction.setPosition(windowCenter, 180.0f);

    // 3. HIGH SCORES
    auto scores = Logic::HighScore::load();
    scorelines.clear();

    // Changed Start Y from 300 to 250 (Closer to instruction)
    float startY = 250.0f;

    for (size_t i = 0; i < scores.size(); i++) {
        sf::Text t;
        t.setFont(font);
        t.setCharacterSize(12);
        t.setFillColor(sf::Color::White);

        t.setString(std::to_string(i + 1) + ". " + std::to_string(scores[i]));

        sf::FloatRect scoreRect = t.getLocalBounds();
        t.setOrigin(scoreRect.left + scoreRect.width / 2.0f, scoreRect.top + scoreRect.height / 2.0f);

        // Reduced spacing between lines from 30 to 25
        t.setPosition(windowCenter, startY + (i * 25));
        scorelines.push_back(t);
    }
}

void MenuState::handleInput() {
    sf::Event event;
    while (window.pollEvent(event)) {
        if (event.type == sf::Event::Closed)
            window.close();
        if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Enter) {
            // Switch to Level State (Replace Menu)
            stateManager.addState(std::make_unique<LevelState>(stateManager, window), true);
        }
    }
}

void MenuState::draw() {
    window.draw(title);
    window.draw(instruction);

    for (const auto& line : scorelines) {
        window.draw(line);
    }
}
} // namespace Representation