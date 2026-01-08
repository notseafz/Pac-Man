
#ifndef PACMANGAME_VICTORYSTATE_H
#define PACMANGAME_VICTORYSTATE_H

#include "State.h"
#include "StateManager.h"

namespace Representation {
class VictoryState : public State {
private:
    StateManager& stateManager;
    sf::RenderWindow& window;
    sf::Font font;
    sf::Text text;

public:
    VictoryState(StateManager& sm, sf::RenderWindow& win);
    void init() override;
    void handleInput() override;
    void update() override {}
    void draw() override;
};
} // namespace Representation
#endif // PACMANGAME_VICTORYSTATE_H