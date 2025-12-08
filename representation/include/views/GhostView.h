
#ifndef PACMANGAME_GHOSTVIEW_H
#define PACMANGAME_GHOSTVIEW_H

#include "EntityView.h"
#include "entities/Ghost.h"
#include "Camera.h"
#include <memory>

namespace Representation {
    class GhostView : public EntityView {
    private:
        std::shared_ptr<Logic::Ghost> model;
        sf::CircleShape sprite;
        Camera& camera;

    public:
        GhostView(std::shared_ptr<Logic::Ghost> m, Camera& cam) : model(m), camera(cam) {
            float radius = 0.02f;
            sf::Vector2f pixelSize = camera.getSizeInPixels(radius * 2, radius * 2);
            sprite.setRadius(pixelSize.x / 2.0f);
            sprite.setFillColor(sf::Color::Red);
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
#endif