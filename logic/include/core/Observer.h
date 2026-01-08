
#ifndef PACMANGAME_OBSERVER_H
#define PACMANGAME_OBSERVER_H

namespace Logic {
class Observer {
public:
    virtual ~Observer() = default;
    virtual void update() = 0;
};
} // namespace Logic

#endif // PACMANGAME_OBSERVER_H
