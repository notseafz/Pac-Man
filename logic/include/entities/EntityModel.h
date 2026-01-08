
#ifndef PACMANGAME_ENTITYMODEL_H
#define PACMANGAME_ENTITYMODEL_H
#include "Subject.h"

namespace Logic {
/**
     * @brief Base class for all game objects.
     *
     * Defines the basic interface for position (x, y) and inherits from Subject
     * to allow Views to observe movement.
 */
class EntityModel : public Subject {
public:
    virtual ~EntityModel() = default;

    virtual float getX() const = 0;
    virtual float getY() const = 0;

    void setPos(float newX, float newY) {}
};
} // namespace Logic

#endif // PACMANGAME_ENTITYMODEL_H
