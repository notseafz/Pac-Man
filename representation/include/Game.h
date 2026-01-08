#pragma once
#include "states/StateManager.h"
#include <SFML/Graphics.hpp>

namespace Representation {
class Game {
public:
    Game();
    void run();

private:
    sf::RenderWindow m_window;
    StateManager m_stateManager;
};
} // namespace Representation