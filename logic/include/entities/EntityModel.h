
#ifndef PACMANGAME_ENTITYMODEL_H
#define PACMANGAME_ENTITYMODEL_H
#include "Subject.h"

namespace Logic {
    class EntityModel : public Subject {
    public:
        virtual ~EntityModel() = default;

        virtual float getX() const = 0;
        virtual float getY() const = 0;

        void setPos(float newX, float newY){

        }
    };
}

#endif //PACMANGAME_ENTITYMODEL_H
