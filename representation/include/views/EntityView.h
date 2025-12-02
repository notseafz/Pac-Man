
#ifndef PACMANGAME_ENTITYVIEW_H
#define PACMANGAME_ENTITYVIEW_H

#include "core/Observer.h"
#include "SFML/Graphics.hpp"

namespace Representation {
    class EntityView : public Logic::Observer {
        virtual void draw(sf::RenderWindow& window) = 0;
    };
}

#endif //PACMANGAME_ENTITYVIEW_H
