
#ifndef PACMANGAME_ENTITYMODEL_H
#define PACMANGAME_ENTITYMODEL_H


namespace Logic {
    class EntityModel {
    public:
        EntityModel() = default;

        virtual float getX() const = 0;
        virtual float getY() const = 0;
    };
}

#endif //PACMANGAME_ENTITYMODEL_H
