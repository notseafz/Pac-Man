#pragma once
#include <SFML/Graphics.hpp>
#include "world/World.h"
#include "ConcreteFactory.h"

namespace Representation {
    class Game {
    public:
        Game();
        void processEvents();
        void run();
    private:
        sf::RenderWindow m_window;

        std::shared_ptr<ConcreteFactory> m_factory;
        Logic::World m_world;
    };
}