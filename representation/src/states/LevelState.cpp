#include "states/LevelState.h"
#include "states/VictoryState.h"
#include "entities/Coin.h"
#include "core/Score.h"
#include "GameOver.h"

namespace Representation {
    LevelState::LevelState(StateManager& sm, sf::RenderWindow& win)
            : stateManager(sm), window(win) {}

    void LevelState::init() {
        factory = std::make_shared<ConcreteFactory>(800, 600);
        world = std::make_unique<Logic::World>(factory);
        scoreView = std::make_shared<ScoreView>();
        Logic::Score::getInstance().addObserver(scoreView);
        Logic::Score::getInstance().resetScore();
    }

    void LevelState::handleInput() {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();

            if (event.type == sf::Event::KeyPressed) {
                if (auto pac = world->getPacMan()) {
                    if (event.key.code == sf::Keyboard::Left)  pac->setDirection(-1, 0);
                    if (event.key.code == sf::Keyboard::Right) pac->setDirection(1, 0);
                    if (event.key.code == sf::Keyboard::Up)    pac->setDirection(0, 1);
                    if (event.key.code == sf::Keyboard::Down)  pac->setDirection(0, -1);
                }
            }
        }
    }

    void LevelState::update() {
        world->update();
        bool levelCleared = true;
        for (const auto& coin : world->getCoins()) {
            if (!coin->getIsCollected()) {
                levelCleared = false;
                break;
            }
        }

        if (levelCleared) {
            stateManager.addState(std::make_unique<VictoryState>(stateManager, window), true);
        }

        if (world->getPacMan()->gameover()) {
            stateManager.addState(std::make_unique<GameOver>(stateManager, window), true);
        }
    }

    void LevelState::draw() {
        for (const auto& wallSprite : factory->getWallSprites()) {
            window.draw(*wallSprite);
        }

        const auto& logicCoins = world->getCoins();
        const auto& spriteCoins = factory->getCoinSprites();

        for (size_t i = 0; i < logicCoins.size(); ++i) {
            if (i < spriteCoins.size()) {
                if (!logicCoins[i]->getIsCollected()) {
                    window.draw(*spriteCoins[i]);
                }
            }
        }
        if (auto view = factory->getPacManView()) {
            view->draw(window);
        }

        for (const auto& ghostview : factory->getGhostviews()) {
            ghostview->draw(window);
        }

        if (scoreView) {
            scoreView->draw(window);
        }

        const auto& logicFruits = world->getFruits();
        const auto& spriteFruits = factory->getFruitSprites();

        for (size_t i = 0; i < logicFruits.size(); ++i) {
            if (i < spriteFruits.size() && !logicFruits[i]->getIsCollected()) {
                window.draw(*spriteFruits[i]);
            }
        }
    }

}