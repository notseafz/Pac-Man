
#ifndef PACMANGAME_STATE_H
#define PACMANGAME_STATE_H

#include <SFML/Graphics.hpp>

namespace Representation {
    class State {
    public:
        virtual ~State() = default;

        virtual void init() = 0;
        virtual void handleInput() = 0;
        virtual void update() = 0;
        virtual void draw() = 0;

        virtual void pause() {}
        virtual void resume() {}
    };
}
#endif //PACMANGAME_STATE_H