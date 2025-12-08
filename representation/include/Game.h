#pragma once
#include <SFML/Graphics.hpp>
#include "states/StateManager.h"

namespace Representation {
    class Game {
    public:
        Game();
        void run();

    private:
        sf::RenderWindow m_window;
        StateManager m_stateManager;
    };
}