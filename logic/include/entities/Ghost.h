#ifndef PACMANGAME_GHOST_H
#define PACMANGAME_GHOST_H

#include "DynamicEntity.h"
#include <vector>
#include <memory>

namespace Logic {

    enum class GhostState { Chase, Frightened };

    // ==========================================
    // BASE GHOST CLASS
    // ==========================================
    class Ghost : public DynamicEntity {
    protected:
        float startX, startY;
        GhostState state;

        float frightenedTimer;
        float activeTimer;
        float spawnDelay;
        bool isActive;

        // Helper
        float getDistance(float x1, float y1, float x2, float y2) const;

        // Virtual function for Target Calculation
        virtual void calculateChaseTarget(float& destX, float& destY,
                                          float targetX, float targetY,
                                          int pacDirX, int pacDirY) = 0;

    public:
        Ghost(float px, float py, float tw, float th, float delay);
        virtual ~Ghost() = default;

        virtual int getTypeIndex() const = 0;

        void resetPosition();
        void setFrightened(bool frightened);
        bool isFrightened() const;
        void setSpeed(float s);

        // standard Update Loop
        virtual void update(float dt, const std::vector<std::shared_ptr<Wall>>& walls,
                            float targetX, float targetY, int pacDirX, int pacDirY);
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

        // Orange overrides the entire update loop for random behavior
        void update(float dt, const std::vector<std::shared_ptr<Wall>>& walls,
                    float targetX, float targetY, int pacDirX, int pacDirY) override;

    protected:
        // Not used, but must be implemented due to pure virtual
        void calculateChaseTarget(float& destX, float& destY, float, float, int, int) override;
    };
}

#endif // PACMANGAME_GHOST_H