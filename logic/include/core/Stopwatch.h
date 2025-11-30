
#ifndef PACMANGAME_STOPWATCH_H
#define PACMANGAME_STOPWATCH_H

#include <chrono>

namespace Logic {
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
    };
}
#endif //PACMANGAME_STOPWATCH_H
