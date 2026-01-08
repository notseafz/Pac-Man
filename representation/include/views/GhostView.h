
#ifndef PACMANGAME_GHOSTVIEW_H
#define PACMANGAME_GHOSTVIEW_H

#include "Camera.h"
#include "EntityView.h"
#include "entities/Ghost.h"
#include <memory>
#include <utility>

namespace Representation {
class GhostView : public EntityView {
private:
    std::shared_ptr<Logic::Ghost> model;
    sf::Sprite sprite;
    Camera& camera;

    sf::IntRect normalRect;
    sf::IntRect scaredRect;

public:
    GhostView(std::shared_ptr<Logic::Ghost> m, Camera& cam, sf::Texture& tex, sf::IntRect normal, sf::IntRect scared)
        : model(m), camera(cam), normalRect(normal), scaredRect(scared) {
        sprite.setTexture(tex);
        sprite.setTextureRect(normalRect);

        sf::Vector2f targetSize = camera.getSizeInPixels(model->getWidth(), model->getHeight());
        sprite.setScale(targetSize.x / normalRect.width, targetSize.y / normalRect.height);

        sprite.setOrigin(normalRect.width / 2.0f, normalRect.height / 2.0f);
    }

    void update() override {
        sf::Vector2f pos = camera.toPixels(model->getX(), model->getY());
        sprite.setPosition(pos);

        if (model->isFrightened()) {
            sprite.setTextureRect(scaredRect);
        } else {
            sprite.setTextureRect(normalRect);
        }

        sprite.setColor(sf::Color::White);
    }

    void draw(sf::RenderWindow& window) override { window.draw(sprite); }
};
} // namespace Representation
#endif