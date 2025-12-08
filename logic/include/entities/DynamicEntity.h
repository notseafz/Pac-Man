
#ifndef PACMANGAME_DYNAMICENTITY_H
#define PACMANGAME_DYNAMICENTITY_H

#include "EntityModel.h"
#include "Wall.h"
#include <vector>
#include <cmath>
#include <algorithm>

namespace Logic {
    class DynamicEntity : public EntityModel {
    protected:
        float x, y;
        float width, height;
        float tileW, tileH;
        float mapOriginY = 1.0f;
        float speed = 0.5f;
        int dirX = 0, dirY = 0;

        bool willCollide(float testX, float testY, const std::vector<std::shared_ptr<Wall>>& walls) {
            float hitW = tileW * 0.5f;
            float hitH = tileH * 0.5f;
            for (const auto& wall : walls) {
                if (std::abs(testX - wall->getX()) * 2.0f < (hitW + wall->getWidth()) &&
                    std::abs(testY - wall->getY()) * 2.0f < (hitH + wall->getHeight())) {
                    return true;
                }
            }
            return false;
        }

    public:
        DynamicEntity(float px, float py, float tw, float th)
                : x(px), y(py), tileW(tw), tileH(th) {
            width = tw * 0.8f;
            height = th * 0.8f;
        }

        float getX() const override { return x; }
        float getY() const override { return y; }
        float getWidth() const { return width; }

        void setMapOriginY(float startY) { mapOriginY = startY; }

        bool tryMove(float dt, const std::vector<std::shared_ptr<Wall>>& walls) {
            float oldX = x;
            float oldY = y;

            float relativeX = x - (-1.0f);
            int col = std::floor(relativeX / tileW);
            float centerX = -1.0f + (col * tileW) + (tileW / 2.0f);

            float relativeY = mapOriginY - y;
            int row = std::floor(relativeY / tileH);
            float centerY = mapOriginY - (row * tileH) - (tileH / 2.0f);

            float nextX = x + (dirX * speed * dt);
            float nextY = y + (dirY * speed * dt);

            float lookAhead = tileW * 0.4f;

            bool moved = false;

            if (!willCollide(nextX + dirX * lookAhead, nextY + dirY * lookAhead, walls)) {
                x = nextX;
                y = nextY;
                moved = true;

                if (dirX != 0) y = centerY;
                if (dirY != 0) x = centerX;
            } else {
                if (dirX != 0) x = centerX;
                if (dirY != 0) y = centerY;
                moved = false;
            }

            if (x != oldX || y != oldY) notify();

            return moved;
        }

        bool isCentered(float tolerance) {
            float relativeX = x - (-1.0f);
            int col = std::floor(relativeX / tileW);
            float centerX = -1.0f + (col * tileW) + (tileW / 2.0f);

            float relativeY = mapOriginY - y;
            int row = std::floor(relativeY / tileH);
            float centerY = mapOriginY - (row * tileH) - (tileH / 2.0f);

            return (std::abs(x - centerX) <= tolerance && std::abs(y - centerY) <= tolerance);
        }

        void snapToGrid() {
            float relativeX = x - (-1.0f);
            int col = std::floor(relativeX / tileW);
            x = -1.0f + (col * tileW) + (tileW / 2.0f);

            float relativeY = mapOriginY - y;
            int row = std::floor(relativeY / tileH);
            y = mapOriginY - (row * tileH) - (tileH / 2.0f);
        }
    };
}
#endif //PACMANGAME_DYNAMICENTITY_H