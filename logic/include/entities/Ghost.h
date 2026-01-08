#ifndef PACMANGAME_GHOST_H
#define PACMANGAME_GHOST_H
#include "DynamicEntity.h"
#include <memory>
#include <vector>

namespace Logic {
enum class GhostState { Chase, Frightened };

class Ghost : public DynamicEntity {
protected:
    float startX, startY;
    GhostState state;

    float frightenedTimer;
    float activeTimer;
    float spawnDelay;
    bool isActive;
    bool hasLeftBox;
    bool justExited;

    float getDistance(float x1, float y1, float x2, float y2) const;

    virtual void calculateChaseTarget(float& destX, float& destY, float targetX, float targetY, int pacDirX,
                                      int pacDirY) = 0;

    bool handleExitLogic(float dt, float pacmanX);

public:
    Ghost(float px, float py, float tw, float th, float delay);
    virtual ~Ghost() = default;

    virtual int getTypeIndex() const = 0;

    void resetPosition();
    void setFrightened(bool frightened);
    bool isFrightened() const;
    void setSpeed(float s);
    void setSpawnDelay(float d);

    virtual void update(float dt, const std::vector<std::shared_ptr<Wall>>& walls, float targetX, float targetY,
                        int pacDirX, int pacDirY);
};

class RedGhost : public Ghost {
public:
    RedGhost(float px, float py, float tw, float th);
    int getTypeIndex() const override;

protected:
    void calculateChaseTarget(float& destX, float& destY, float tX, float tY, int, int) override;
};

class PinkGhost : public Ghost {
public:
    PinkGhost(float px, float py, float tw, float th);
    int getTypeIndex() const override;

protected:
    void calculateChaseTarget(float& destX, float& destY, float tX, float tY, int pdX, int pdY) override;
};

class BlueGhost : public Ghost {
public:
    BlueGhost(float px, float py, float tw, float th);
    int getTypeIndex() const override;

protected:
    void calculateChaseTarget(float& destX, float& destY, float tX, float tY, int pdX, int pdY) override;
};

class OrangeGhost : public Ghost {
public:
    OrangeGhost(float px, float py, float tw, float th);
    int getTypeIndex() const override;

    void update(float dt, const std::vector<std::shared_ptr<Wall>>& walls, float targetX, float targetY, int pacDirX,
                int pacDirY) override;

protected:
    void calculateChaseTarget(float& destX, float& destY, float, float, int, int) override;
};
} // namespace Logic
#endif // PACMANGAME_GHOST_H