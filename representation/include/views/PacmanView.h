
#ifndef PACMANGAME_PACMANVIEW_H
#define PACMANGAME_PACMANVIEW_H

#include "Camera.h"
#include "EntityView.h"
#include "Stopwatch.h"
#include "entities/PacMan.h"
#include <iostream>
#include <memory>
#include <utility>

namespace Representation {
class PacManView : public EntityView {
private:
    std::shared_ptr<Logic::PacMan> model;
    sf::Sprite sprite;
    Camera& camera;

    // animation
    std::vector<sf::IntRect> animRight;
    std::vector<sf::IntRect> animLeft;
    std::vector<sf::IntRect> animUp;
    std::vector<sf::IntRect> animDown;
    std::vector<sf::IntRect>* currentAnim;

    int frameIndex = 0;
    float animationTimer = 0.0f;

public:
    PacManView(std::shared_ptr<Logic::PacMan> m, Camera& cam, sf::Texture& tex, std::vector<sf::IntRect> right,
               std::vector<sf::IntRect> left, std::vector<sf::IntRect> up, std::vector<sf::IntRect> down)
        : model(m), camera(cam), animRight(right), animLeft(left), animUp(up), animDown(down) {
        sprite.setTexture(tex);
        currentAnim = &animRight;
        sprite.setTextureRect(animRight[0]);

        sf::Vector2f targetSize = camera.getSizeInPixels(model->getWidth(), model->getHeight());
        sprite.setScale(targetSize.x / 33.0f, targetSize.y / 33.0f);
        sprite.setOrigin(33.0f / 2.0f, 33.0f / 2.0f);
    }

    void update() override {
        sf::Vector2f pos = camera.toPixels(model->getX(), model->getY());
        sprite.setPosition(pos);

        int dx = model->getDirX();
        int dy = model->getDirY();
        if (dx == 1)
            currentAnim = &animRight;
        if (dx == -1)
            currentAnim = &animLeft;
        if (dy == 1)
            currentAnim = &animUp;
        if (dy == -1)
            currentAnim = &animDown;

        float dt = Logic::Stopwatch::getInstance().getDeltaTime();

        if (dx != 0 || dy != 0) {
            animationTimer += dt;
            if (animationTimer >= 0.05f) {
                animationTimer = 0;
                frameIndex = (frameIndex + 1) % 4;
            }
        } else {
            frameIndex = 1;
        }

        sprite.setTextureRect((*currentAnim)[frameIndex]);

        sprite.setRotation(0);
    }
    void draw(sf::RenderWindow& window) override { window.draw(sprite); }
};
} // namespace Representation

#endif // PACMANGAME_PACMANVIEW_H
