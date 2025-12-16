
#ifndef PACMANGAME_GHOST_H
#define PACMANGAME_GHOST_H

#include "DynamicEntity.h"
#include <cstdlib>

namespace Logic {

    enum class GhostType {Red, Pink, Blue, Purple};
    enum class GhostState {Chase, Frightened};

    class Ghost : public DynamicEntity {
    private:
        float startX, startY;
        GhostType type;
        GhostState state = GhostState::Chase;
        float frightenedTimer = 0.0f;

        float getDistance(float x1, float y1, float x2, float y2) {
            return std::abs(x1 - x2) + std::abs(y1-y2);
        }
    public:
        Ghost(float px, float py, float tw, float th, int ghostIndex)
                : DynamicEntity(px, py, tw, th) {
            dirX = 1; dirY = 0;
            speed = 0.3f;
            type = static_cast<GhostType>(ghostIndex % 4);
        }

        void resetPosition() {
            x = startX;
            y = startY;
            dirX = 1; dirY = 0;
            state = GhostState::Chase;
            notify();
        }

        void setFrightened(bool frightened) {
            if (frightened) {
                state = GhostState::Frightened;
                frightenedTimer = 10.0f;
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

            if (state == GhostState::Frightened) {
                frightenedTimer -= dt;
                if (frightenedTimer <= 0) {
                    setFrightened(false);
                }
            }
            bool moved = tryMove(dt, walls);

            float destX = targetX;
            float destY = targetY;

            if (state == GhostState::Frightened) {
                // pick a corner based on ghost type to spread them out
                if (type == GhostType::Red)       { destX = -1.0f; destY = 1.0f; }  // Top Left
                else if (type == GhostType::Pink) { destX = 1.0f;  destY = 1.0f; }  // Top Right
                else if (type == GhostType::Blue) { destX = -1.0f; destY = -1.0f; } // Bot Left
                else                              { destX = 1.0f;  destY = -1.0f; } // Bot Right
            }
            else if (type == GhostType::Pink) {
                destX += pacDirX * (tileW * 4.0f);
                destY += pacDirY * (tileH * 4.0f);
            }

            float tolerance = speed * dt * 1.5f;

            if (!moved || isCentered(tolerance)) {
                if (!moved) snapToGrid();
                struct Candidate {
                    int dx, dy;
                    float dist;
                };
                std::vector<Candidate> options;

                int dirs[4][2] = {{0,  1},
                                  {0,  -1},
                                  {-1, 0},
                                  {1,  0}};

                for (auto &d: dirs) {
                    if (d[0] == -dirX && d[1] == -dirY && moved) continue;
                    float nextTileX = x + d[0] * tileW;
                    float nextTileY = y + d[1] * tileH;

                    if (!willCollide(nextTileX, nextTileY, walls)) {
                        float dist = getDistance(nextTileX, nextTileY, destX, destY);
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
    };
}
#endif //PACMANGAME_GHOST_H