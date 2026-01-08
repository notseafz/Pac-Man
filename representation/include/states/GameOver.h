
#ifndef PACMANGAME_GAMEOVER_H
#define PACMANGAME_GAMEOVER_H

#include "State.h"
#include "StateManager.h"
namespace Representation {
class GameOver : public State {
    StateManager& stateManager;
    sf::RenderWindow& window;
    sf::Font font;
    sf::Text text;

public:
    GameOver(StateManager& sm, sf::RenderWindow& win);
    void init() override;
    void handleInput() override;
    void update() override {}
    void draw() override;
};
} // namespace Representation

#endif
