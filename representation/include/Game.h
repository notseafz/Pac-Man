#pragma once
#include <SFML/Graphics.hpp>
#include "world/World.h" // Logic Link

namespace Representation {
    class Game {
    public:
        Game();
        void run();
    private:
        sf::RenderWindow m_window;
        Logic::World m_world;
    };
}