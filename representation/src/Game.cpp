#include "Game.h"
#include "states/MenuState.h"

namespace Representation {
Game::Game() : m_window(sf::VideoMode(800, 600), "Pac-Man Project") {
    m_window.setFramerateLimit(60);

    m_stateManager.addState(std::make_unique<MenuState>(m_stateManager, m_window));
}

void Game::run() {
    while (m_window.isOpen()) {
        m_stateManager.processStateChanges();
        auto& currentState = m_stateManager.getActiveState();

        if (currentState) {
            currentState->handleInput();
            currentState->update();

            m_window.clear();
            currentState->draw();
            m_window.display();
        }
    }
}
} // namespace Representation