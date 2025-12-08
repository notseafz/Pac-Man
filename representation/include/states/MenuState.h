
#ifndef PACMANGAME_MENUSTATE_H
#define PACMANGAME_MENUSTATE_H

#include "State.h"
#include "StateManager.h"

namespace Representation {
    class MenuState : public State {
    private:
        StateManager& stateManager;
        sf::RenderWindow& window;
        sf::Font font;
        sf::Text text;

    public:
        MenuState(StateManager& sm, sf::RenderWindow& win);
        void init() override;
        void handleInput() override;
        void update() override {}
        void draw() override;
    };
}
#endif //PACMANGAME_MENUSTATE_H
