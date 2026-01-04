#include "entities/Ghost.h"
#include <cmath>
#include <cstdlib>
#include <algorithm>
namespace Logic {
    Ghost::Ghost(float px, float py, float tw, float th, float delay)
            : DynamicEntity(px, py, tw, th), startX(px), startY(py),
              state(GhostState::Chase), frightenedTimer(0.0f),
              activeTimer(0.0f), spawnDelay(delay), isActive(false), hasLeftBox(false), justExited(false)
    {
        dirX = 1; dirY = 0;
        speed = 0.3f;
    }

    float Ghost::getDistance(float x1, float y1, float x2, float y2) const {
        return std::abs(x1 - x2) + std::abs(y1 - y2);
    }

    void Ghost::resetPosition() {
        x = startX;
        y = startY;
        dirX = 1; dirY = 0;
        state = GhostState::Chase;
        isActive = false;
        activeTimer = 0.0f;
        hasLeftBox = false;
        justExited = false;

        snapToGrid();
        notify();
    }

    void Ghost::setFrightened(bool frightened) {
        if (!isActive) return;
        if (frightened) {
            state = GhostState::Frightened;
            frightenedTimer = 5.0f;
            speed = 0.2f;
            dirX = -dirX; dirY = -dirY;
        } else {
            state = GhostState::Chase;
            speed = 0.3f;
        }
        notify();
    }

    bool Ghost::isFrightened() const {
        return state == GhostState::Frightened;
    }

    void Ghost::setSpeed(float s) {
        speed = s;
    }

    bool Ghost::handleExitLogic(float dt) {
        // spawn timer
        if (!isActive) {
            activeTimer += dt;
            if (activeTimer >= spawnDelay) {
                isActive = true;
            } else {
                return true; //
            }
        }

        if (hasLeftBox) return false;

        float moveStep = speed * dt;
        float exitY = startY + (tileH * 2.0f);
        float exitX = 0.0f;

        if (getTypeIndex() == 0 || getTypeIndex() == 1) {  // red or pink
            exitX = -tileW * 0.5f;
        } else {  // Blue or Orange
            exitX = tileW * 0.5f;
        }

        if (std::abs(x - exitX) > moveStep) {
            if (x > exitX) x -= moveStep; // slide Left
            else           x += moveStep; // slide Right

            dirX = (x > exitX) ? -1 : 1;
            dirY = 0;
        }
        else {
            x = exitX;

            if (y < exitY) {
                y += moveStep;
                dirX = 0;
                dirY = 1;
            }

            if (y >= exitY) {
                y = exitY;
                hasLeftBox = true;
                justExited = true;

                if (getTypeIndex() == 0 || getTypeIndex() == 1) dirX = -1;
                else dirX = 1;

                dirY = 0;
                snapToGrid();

                notify();
                return false;
            }
        }

        notify();
        return true;
    }

    void Ghost::update(float dt, const std::vector<std::shared_ptr<Wall>>& walls,
                       float targetX, float targetY, int pacDirX, int pacDirY)
    {
        if (handleExitLogic(dt)) return;

        if (state == GhostState::Frightened) {
            frightenedTimer -= dt;
            if (frightenedTimer <= 0) setFrightened(false);
        }

        bool moved = tryMove(dt, walls);
        float tolerance = speed * dt * 1.5f;

        if (!moved || isCentered(tolerance)) {
            if (!moved) snapToGrid();

            float destX = targetX;
            float destY = targetY;

            if (state == GhostState::Frightened) {
                // run to corners based on type
                int idx = getTypeIndex();
                if (idx == 0)      { destX = -1.0f; destY = 1.0f; }
                else if (idx == 1) { destX = 1.0f;  destY = 1.0f; }
                else if (idx == 2) { destX = -1.0f; destY = -1.0f; }
                else               { destX = 1.0f;  destY = -1.0f; }
            } else {
                calculateChaseTarget(destX, destY, targetX, targetY, pacDirX, pacDirY);
            }

            // Pathfinding
            struct Candidate { int dx, dy; float dist; };
            std::vector<Candidate> options;
            int dirs[4][2] = {{0,1}, {0,-1}, {-1,0}, {1,0}};

            for (auto& d : dirs) {
                if (d[0] == -dirX && d[1] == -dirY && moved) continue;
                if (justExited && d[1] == -1) continue;

                if (!willCollide(x + d[0]*tileW, y + d[1]*tileH, walls)) {
                    float dist = getDistance(x + d[0]*tileW, y + d[1]*tileH, destX, destY);
                    options.push_back({d[0], d[1], dist});
                }
            }

            if (!options.empty()) {
                auto best = options[0];
                for(auto& opt : options) if(opt.dist < best.dist) best = opt;

                std::vector<Candidate> ties;
                for(auto& opt : options) if (std::abs(opt.dist - best.dist) < 0.001f) ties.push_back(opt);

                int r = rand() % ties.size();
                if (dirX != ties[r].dx || dirY != ties[r].dy) {
                    snapToGrid();
                    dirX = ties[r].dx;
                    dirY = ties[r].dy;


                    if (justExited) justExited = false;
                }
            } else {
                dirX = -dirX; dirY = -dirY;
            }
        }
        if (moved) notify();
    }

    // RED GHOST
    RedGhost::RedGhost(float px, float py, float tw, float th) : Ghost(px, py, tw, th, 0.0f) {}
    int RedGhost::getTypeIndex() const { return 0; }
    void RedGhost::calculateChaseTarget(float& destX, float& destY, float tX, float tY, int, int) {
        destX = tX;
        destY = tY;
    }


    // PINK GHOST
    PinkGhost::PinkGhost(float px, float py, float tw, float th) : Ghost(px, py, tw, th, 0.0f) {}
    int PinkGhost::getTypeIndex() const { return 1; }
    void PinkGhost::calculateChaseTarget(float& destX, float& destY, float tX, float tY, int pdX, int pdY) {
        destX = tX + pdX * (tileW * 4.0f);
        destY = tY + pdY * (tileH * 4.0f);
    }


    // BLUE GHOST
    BlueGhost::BlueGhost(float px, float py, float tw, float th) : Ghost(px, py, tw, th, 5.0f) {}
    int BlueGhost::getTypeIndex() const { return 2; }
    void BlueGhost::calculateChaseTarget(float& destX, float& destY, float tX, float tY, int pdX, int pdY) {
        destX = tX + pdX * (tileW * 4.0f);
        destY = tY + pdY * (tileH * 4.0f);
    }


    // ORANGE GHOST
    OrangeGhost::OrangeGhost(float px, float py, float tw, float th) : Ghost(px, py, tw, th, 10.0f) {}
    int OrangeGhost::getTypeIndex() const { return 3; }

    void OrangeGhost::calculateChaseTarget(float& destX, float& destY, float, float, int, int) {
        destX = 0; destY = 0; // unused
    }

    void OrangeGhost::update(float dt, const std::vector<std::shared_ptr<Wall>>& walls,
                             float targetX, float targetY, int pacDirX, int pacDirY)
    {
        // check exit logic first
        if (handleExitLogic(dt)) return;

        if (state == GhostState::Frightened) {
            frightenedTimer -= dt;
            if (frightenedTimer <= 0) setFrightened(false);
        }

        if (state == GhostState::Frightened) {
            Ghost::update(dt, walls, targetX, targetY, pacDirX, pacDirY);
            return;
        }

        // random Movement
        bool moved = tryMove(dt, walls);
        float tolerance = speed * dt * 1.5f;

        if (!moved || isCentered(tolerance)) {
            if (!moved) snapToGrid();

            int openPaths = 0;
            if (!willCollide(x+tileW, y, walls)) openPaths++;
            if (!willCollide(x-tileW, y, walls)) openPaths++;
            if (!willCollide(x, y+tileH, walls)) openPaths++;
            if (!willCollide(x, y-tileH, walls)) openPaths++;

            bool pickNew = !moved;
            if (moved && openPaths > 2 && (rand() % 2 == 0)) pickNew = true;

            if (pickNew) {
                std::vector<std::pair<int,int>> valid;
                if (!willCollide(x+tileW, y, walls) && dirX != -1) valid.push_back({1,0});
                if (!willCollide(x-tileW, y, walls) && dirX != 1) valid.push_back({-1,0});
                if (!willCollide(x, y+tileH, walls) && dirY != -1) valid.push_back({0,1});
                if (!willCollide(x, y-tileH, walls) && dirY != 1) valid.push_back({0,-1});

                if (!valid.empty()) {
                    int r = rand() % valid.size();
                    dirX = valid[r].first;
                    dirY = valid[r].second;
                    snapToGrid();
                } else {
                    dirX = -dirX; dirY = -dirY;
                }
            }
        }
        if (moved) notify();
    }
}