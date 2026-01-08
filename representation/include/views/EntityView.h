
#ifndef PACMANGAME_ENTITYVIEW_H
#define PACMANGAME_ENTITYVIEW_H

#include "SFML/Graphics.hpp"
#include "core/Observer.h"

namespace Representation {
class EntityView : public Logic::Observer {
    virtual void draw(sf::RenderWindow& window) = 0;
};
} // namespace Representation

#endif // PACMANGAME_ENTITYVIEW_H
