
#ifndef PACMANGAME_LEVELSTATE_H
#define PACMANGAME_LEVELSTATE_H

#include "State.h"
#include "StateManager.h"
#include "ConcreteFactory.h"
#include "world/World.h"
#include "views/ScoreView.h"
#include <memory>

namespace Representation {
    class LevelState : public State {
    private:
        StateManager& stateManager;
        sf::RenderWindow& window;
        std::shared_ptr<ConcreteFactory> factory;
        std::unique_ptr<Logic::World> world;
        std::shared_ptr<ScoreView> scoreView;

    public:
        LevelState(StateManager& sm, sf::RenderWindow& win);
        void init() override;
        void handleInput() override;
        void update() override;
        void draw() override;
    };
}
#endif //PACMANGAME_LEVELSTATE_H