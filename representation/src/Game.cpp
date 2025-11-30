#include "Game.h"

namespace Representation {
    Game::Game()
            : m_window(sf::VideoMode(800, 600), "Pac-Man"),
              m_factory(std::make_shared<ConcreteFactory>(800,600)),
              m_world(m_factory) // Pass aspect ratio (1.33)
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

            m_world.update();
            m_window.clear();

            for (const auto& wallSprite : m_factory->getWallSprites()) {
                m_window.draw(*wallSprite);
            }

            m_window.display();
        }
    }
}