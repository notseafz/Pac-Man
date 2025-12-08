
#ifndef PACMANGAME_GHOST_H
#define PACMANGAME_GHOST_H

#include "DynamicEntity.h"
#include <cstdlib>

namespace Logic {
    class Ghost : public DynamicEntity {
    public:
        Ghost(float px, float py, float tw, float th)
                : DynamicEntity(px, py, tw, th) {
            dirX = 1; dirY = 0;
            speed = 0.3f;
        }

        void update(float dt, const std::vector<std::shared_ptr<Wall>>& walls) {
            bool moved = tryMove(dt, walls);
            if (!moved) {
                int pick = rand() % 4;
                dirX = 0; dirY = 0;
                if (pick == 0) dirX = 1;
                else if (pick == 1) dirX = -1;
                else if (pick == 2) dirY = 1;
                else if (pick == 3) dirY = -1;
            }
        }
    };
}
#endif //PACMANGAME_GHOST_H