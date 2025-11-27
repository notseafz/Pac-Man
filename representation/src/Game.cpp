#include "Game.h"

namespace Representation {
    Game::Game()
        : m_window(sf::VideoMode(800, 600), "Pac-Man Project"), m_world()
    {
        m_window.setFramerateLimit(60);
    }

    void Game::run() {
        while (m_window.isOpen()) {
            sf::Event event;
            while (m_window.pollEvent(event)) {
                if (event.type == sf::Event::Closed)
                    m_window.close();
            }

            m_world.update(); // Update Logic

            m_window.clear();
            // Draw calls will go here
            m_window.display();
        }
    }
}