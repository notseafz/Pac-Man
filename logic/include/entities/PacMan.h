#ifndef PACMANGAME_PACMAN_H
#define PACMANGAME_PACMAN_H

#include "DynamicEntity.h"

namespace Logic {
    class PacMan : public DynamicEntity {
    private:
        int nextDirX = 0;
        int nextDirY = 0;
        float startX, startY;
        int lives = 3;
        bool isDead = false;

    public:
        PacMan(float px, float py, float tw, float th, float startX, float startY) : DynamicEntity(px, py, tw, th),
                                                                                     startX(startX), startY(startY) {}

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
            if (nextDirX != 0 || nextDirY != 0) {
                float tolerance = speed * deltaTime * 1.5f;

                if (isCentered(tolerance)) {
                    float lookAhead = tileW;
                    if (!willCollide(x + nextDirX * lookAhead, y + nextDirY * lookAhead, walls)) {
                        snapToGrid();
                        dirX = nextDirX;
                        dirY = nextDirY;
                        nextDirX = 0;
                        nextDirY = 0;
                    }
                }
            }
            tryMove(deltaTime, walls);
        }

        void die() {
            lives--;

            if (lives == 0) {
                isDead = true;
            }

        };

        void resetPostition() {
            x = startX;
            y = startY;
            dirY= 0;
            dirX = 0;
            nextDirY = 0;
            nextDirX = 0;
            notify();
        }

        int getLives() const {
            return lives;
        }

        bool gameover() const {
            return isDead;
        }
    };
}
#endif //PACMANGAME_PACMAN_H