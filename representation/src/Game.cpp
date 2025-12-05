#include "Game.h"
#include "entities/PacMan.h"
#include "entities/Coin.h"

namespace Representation {
    Game::Game()
            : m_window(sf::VideoMode(800, 600), "Pac-Man"),
              m_factory(std::make_shared<ConcreteFactory>(800,600)),
              m_world(m_factory) // Pass aspect ratio (1.33)
    {
        m_window.setFramerateLimit(60);

        scoreView = std::make_shared<ScoreView>();
        Logic::Score::getInstance().addObserver(scoreView);
    }

    void Game::processEvents() {
        sf::Event event;
        while (m_window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                m_window.close();

            // input
            if (event.type == sf::Event::KeyPressed) {
                if (m_world.getPacMan()) {
                    if (event.key.code == sf::Keyboard::Left)  m_world.getPacMan()->setDirection(-1, 0);
                    if (event.key.code == sf::Keyboard::Right) m_world.getPacMan()->setDirection(1, 0);
                    if (event.key.code == sf::Keyboard::Up)    m_world.getPacMan()->setDirection(0, 1);
                    if (event.key.code == sf::Keyboard::Down)  m_world.getPacMan()->setDirection(0, -1);
                }
            }
        }
    }

    void Game::run() {
        while (m_window.isOpen()) {

            processEvents();
            m_world.update();
            m_window.clear();

            for (const auto& wallSprite : m_factory->getWallSprites()) {
                m_window.draw(*wallSprite);
            }

//            for (const auto& coin : m_factory->getCoinSprites()) {
//                m_window.draw(*coin);
//            }

            const auto& logicCoins = m_world.getCoins();
            const auto& spriteCoins = m_factory->getCoinSprites();

            for (size_t i = 0; i < logicCoins.size(); i++) {
                if (i < spriteCoins.size()) {
                    if (!logicCoins[i]->getIsCollected()) {
                        m_window.draw(*spriteCoins[i]);
                    }
                }
            }

            if (auto view = m_factory->getPacManView()) {
                view->draw(m_window);
            }

            if (scoreView) {
                scoreView->draw(m_window);
            }
            m_window.display();
        }
    }
}