
#ifndef PACMANGAME_ENTITYVIEW_H
#define PACMANGAME_ENTITYVIEW_H

#include "SFML/Graphics.hpp"
#include "core/Observer.h"

namespace Representation {
/**
 * @brief Base class for visual representation.
 *
 * Inherits from Observer to automatically update visuals when Logic changes.
 */
class EntityView : public Logic::Observer {
    virtual void draw(sf::RenderWindow& window) = 0;
};
} // namespace Representation

#endif // PACMANGAME_ENTITYVIEW_H
