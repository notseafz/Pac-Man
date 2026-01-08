

#ifndef PACMANGAME_CAMERA_H
#define PACMANGAME_CAMERA_H

#include <SFML/Graphics.hpp>

namespace Representation {
/**
 * @brief Utility for coordinate conversion.
 *
 * Maps normalized Logic coordinates [-1, 1] to Screen pixels [0, 800].
 */
class Camera {
private:
    int screenWidth;
    int screenHeight;

public:
    Camera(int width, int height) : screenWidth(width), screenHeight(height) {}

    sf::Vector2f toPixels(float logicX, float logicY) const {
        float pixelX = (logicX + 1.0f) * 0.5f * screenWidth;
        float pixelY = (1.0f - logicY) * 0.5f * screenHeight;
        return sf::Vector2f(pixelX, pixelY);
    }

    sf::Vector2f getSizeInPixels(float logicW, float logicH) const {
        float pixelW = (logicW / 2.0f) * screenWidth;
        float pixelH = (logicH / 2.0f) * screenHeight;
        return sf::Vector2f(pixelW, pixelH);
    }
};
} // namespace Representation

#endif // PACMANGAME_CAMERA_H
