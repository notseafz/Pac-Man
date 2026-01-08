
#ifndef PACMANGAME_STOPWATCH_H
#define PACMANGAME_STOPWATCH_H

#include <chrono>

namespace Logic {
/**
     * @brief Singleton class for time management.
     *
     * Calculates Delta Time (dt) to ensure frame-rate independent movement.
 */
class Stopwatch {
private:
    static Stopwatch* instance;
    std::chrono::high_resolution_clock::time_point lastTime;
    float deltaTime;

    Stopwatch();

public:
    static Stopwatch& getInstance();

    Stopwatch(const Stopwatch&) = delete;
    void operator=(const Stopwatch&) = delete;

    void tick();
    float getDeltaTime() const;

    void reset() {
        lastTime = std::chrono::high_resolution_clock::now();
        deltaTime = 0.0f;
    }
};
} // namespace Logic
#endif // PACMANGAME_STOPWATCH_H
