
#ifndef PACMANGAME_PACMANVIEW_H
#define PACMANGAME_PACMANVIEW_H

#include "EntityView.h"
#include "entities/PacMan.h"
#include "Camera.h"
#include <memory>
#include <utility>

namespace Representation {
    class PacManView : public EntityView {
    private:
        std::shared_ptr<Logic::PacMan> model;
        sf::Sprite sprite;
        Camera& camera;
    public:
        PacManView(std::shared_ptr<Logic::PacMan> m, Camera& cam, sf::Texture& tex, sf::IntRect rect)
                : model(std::move(m)), camera(cam)
        {
            sprite.setTexture(tex);
            sprite.setTextureRect(rect);

            sf::Vector2f targetSize = camera.getSizeInPixels(model->getWidth(), model->getHeight());
            sprite.setScale(targetSize.x / rect.width, targetSize.y / rect.height);

            sprite.setOrigin(rect.width / 2.0f, rect.height / 2.0f);
        }

        void update() override {
            sf::Vector2f pos = camera.toPixels(model->getX(), model->getY());
            sprite.setPosition(pos);

            int dx = model->getDirX();
            int dy = model->getDirY();
            if (dx == 1) sprite.setRotation(0);
            if (dx == -1) sprite.setRotation(180);
            if (dy == 1) sprite.setRotation(-90);
            if (dy == -1) sprite.setRotation(90);
        }
        void draw(sf::RenderWindow& window) override {
            window.draw(sprite);
        }
    };
}

#endif //PACMANGAME_PACMANVIEW_H
