#ifndef PACMANGAME_PACMAN_H
#define PACMANGAME_PACMAN_H

#include "EntityModel.h"
#include "Wall.h"
#include <vector>
#include <cmath>
#include <algorithm>

namespace Logic {
    class PacMan : public EntityModel {
    private:
        float x, y;
        float width, height;
        float tileW, tileH;
        float mapOriginY = 1.0f;

        float speed = 0.5f;
        int dirX = 0;
        int dirY = 0;
        int nextDirX = 0;
        int nextDirY = 0;

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
        PacMan(float startX, float startY, float tw, float th)
                : x(startX), y(startY), tileW(tw), tileH(th)
        {
            width = tw * 0.8f;
            height = th * 0.8f;
        }

        float getX() const override { return x; }
        float getY() const override { return y; }
        float getWidth() const { return width; }
        float getHeight() const { return height; }

        void setMapOriginY(float startY) {
            mapOriginY = startY;
        }

        void setDirection(int dx, int dy) {
            if ((dx == -dirX && dy == -dirY) && (dx != 0 || dy != 0)) {
                dirX = dx;
                dirY = dy;
                nextDirX = 0;
                nextDirY = 0;
            } else {
                nextDirX = dx;
                nextDirY = dy;
            }
        }

        void update(float deltaTime, const std::vector<std::shared_ptr<Wall>>& walls) {
            float oldX = x;
            float oldY = y;

            float relativeX = x - (-1.0f);
            int col = std::floor(relativeX / tileW);
            float centerX = -1.0f + (col * tileW) + (tileW / 2.0f);

            float relativeY = mapOriginY - y;
            int row = std::floor(relativeY / tileH);
            float centerY = mapOriginY - (row * tileH) - (tileH / 2.0f);

            if (nextDirX != 0 || nextDirY != 0) {
                float distX = std::abs(x - centerX);
                float distY = std::abs(y - centerY);
                float tolerance = speed * deltaTime * 1.5f;

                if (distX <= tolerance && distY <= tolerance) {
                    if (!willCollide(centerX + nextDirX * tileW, centerY + nextDirY * tileH, walls)) {

                        x = centerX;
                        y = centerY;

                        dirX = nextDirX;
                        dirY = nextDirY;
                        nextDirX = 0;
                        nextDirY = 0;
                    }
                }
            }

            float moveStep = speed * deltaTime;
            float nextX = x + (dirX * moveStep);
            float nextY = y + (dirY * moveStep);

            float lookAhead = tileW * 0.4f;

            if (!willCollide(nextX + dirX * lookAhead, nextY + dirY * lookAhead, walls)) {
                x = nextX;
                y = nextY;

                if (dirX != 0) y = centerY;
                if (dirY != 0) x = centerX;
            }
            else {
                if (dirX != 0) x = centerX;
                if (dirY != 0) y = centerY;
            }

            if (x != oldX || y != oldY) notify();
        }
    };
}
#endif //PACMANGAME_PACMAN_H