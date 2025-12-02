
#ifndef PACMANGAME_PACMANVIEW_H
#define PACMANGAME_PACMANVIEW_H

#include "EntityView.h"
#include "entities/PacMan.h"
#include "Camera.h"
#include <memory>

namespace Representation {
    class PacManView : public EntityView {
    private:
        std::shared_ptr<Logic::PacMan> model;
        sf::CircleShape sprite;
        Camera& camera;
    public:
        PacManView(std::shared_ptr<Logic::PacMan> pacManModel, Camera& cam)
                : model(pacManModel), camera(cam)
        {
            float radiusLogic = 0.03f;
            sf::Vector2f pixelSize = camera.getSizeInPixels(radiusLogic * 2.0f, radiusLogic * 2.0f);

            sprite.setRadius(pixelSize.x / 2.0f);
            sprite.setFillColor(sf::Color::Yellow);
            sprite.setOrigin(pixelSize.x / 2.0f, pixelSize.x / 2.0f);
            update();
        }
        void update() override {
            sf::Vector2f pos = camera.toPixels(model->getX(), model->getY());
            sprite.setPosition(pos);
        }
        void draw(sf::RenderWindow& window) override {
            window.draw(sprite);
        }
    };
}

#endif //PACMANGAME_PACMANVIEW_H
