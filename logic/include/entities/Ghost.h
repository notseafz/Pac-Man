
#ifndef PACMANGAME_GHOST_H
#define PACMANGAME_GHOST_H

#include "DynamicEntity.h"
#include <cstdlib>

namespace Logic {

    enum class GhostType {Red, Pink, Blue, Orange};
    enum class GhostState {Chase, Frightened};

    class Ghost : public DynamicEntity {
    private:
        float startX, startY;
        GhostType type;
        GhostState state = GhostState::Chase;
        float frightenedTimer = 0.0f;

        float activeTimer = 0.0f;
        bool isActive = false;
        bool hasLeftBox = false;

        float getDistance(float x1, float y1, float x2, float y2) {
            return std::abs(x1 - x2) + std::abs(y1-y2);
        }
    public:
        Ghost(float px, float py, float tw, float th, int ghostIndex)
                : DynamicEntity(px, py, tw, th), startX(px), startY(py) {
            dirX = 1; dirY = 0;
            speed = 0.3f;
            type = static_cast<GhostType>(ghostIndex % 4);
        }

        void resetPosition() {
            x = startX;
            y = startY;
            dirX = 1; dirY = 0;
            state = GhostState::Chase;
            frightenedTimer = 0.0f;
            isActive = false;
            hasLeftBox = false;
            notify();
        }

        void setFrightened(bool frightened) {
            if (!hasLeftBox) return;
            if (frightened) {
                state = GhostState::Frightened;
                frightenedTimer = 5.0f;
                speed = 0.2f;

                dirX = -dirX;
                dirY = -dirY;
            }
            else {
                state = GhostState::Chase;
                speed = 0.3f;
            }
            notify();
        }

        bool isFrightened() const {
            return state == GhostState::Frightened;
        }

        void update(float dt, const std::vector<std::shared_ptr<Wall>>& walls, float targetX, float targetY, int pacDirX, int pacDirY) {

            if (!isActive) {
                activeTimer += dt;
                float waitTime = (type == GhostType::Blue) ? 5.0f : (type == GhostType::Orange) ? 10.0f : 0.0f;
                if (activeTimer >= waitTime) isActive = true;
                else return; // Don't move
            }

            if (state == GhostState::Frightened) {
                frightenedTimer -= dt;
                if (frightenedTimer <= 0) {
                    setFrightened(false);
                }
            }
            bool moved = tryMove(dt, walls);
            float tolerance = speed * dt * 1.5f;

            if (!moved || isCentered(tolerance)) {
                // exit out of box logic
                float destX, destY;
                if (!hasLeftBox && y > startY + (tileH * 3.0f)) {
                    hasLeftBox = true;
                }

                if (!hasLeftBox) {
                    destX = 0.0f;
                    destY = 1.0f;
                }
                else {
                    // normal AI Logic
                    destX = targetX;
                    destY = targetY;

                    if (state == GhostState::Frightened) {
                        if (type == GhostType::Red)       { destX = -1.0f; destY = 1.0f; }
                        else if (type == GhostType::Pink) { destX = 1.0f;  destY = 1.0f; }
                        else if (type == GhostType::Blue) { destX = -1.0f; destY = -1.0f; }
                        else                              { destX = 1.0f;  destY = -1.0f; }
                    }
                    else if (type == GhostType::Pink || type == GhostType::Blue) {
                        destX += pacDirX * (tileW * 4.0f);
                        destY += pacDirY * (tileH * 4.0f);
                    }
                }

            struct Candidate { int dx, dy; float dist;};
            std::vector<Candidate> options;
            int dirs[4][2] = {{0,1}, {0,-1}, {-1,0}, {1,0}};

            for (auto& d : dirs) {
                // reverse when stuck
                if (d[0] == -dirX && d[1] == -dirY && moved) continue;

                if (!willCollide(x + d[0]*tileW, y + d[1]*tileH, walls)) {
                    float dist = getDistance(x + d[0]*tileW, y + d[1]*tileH, destX, destY);
                    options.push_back({d[0], d[1], dist});
                }
            }

                if (!options.empty()) {
                    auto best = options[0];
                    for (auto &opt: options) {
                        if (opt.dist < best.dist) best = opt;
                    }

                    if (dirX != best.dx || dirY != best.dy) {
                        snapToGrid();
                        dirX = best.dx;
                        dirY = best.dy;
                    }
                } else {
                    // reverse
                    dirX = -dirX;
                    dirY = -dirY;
                }
            }
            if (moved) notify();
        }

        void setSpeed(float new_speed) {
            speed = new_speed;
        }
        //float getSpeed() const {return speed;}
    };
}
#endif //PACMANGAME_GHOST_H