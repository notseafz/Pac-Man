
#ifndef PACMANGAME_SUBJECT_H
#define PACMANGAME_SUBJECT_H

#include "Observer.h"
#include <algorithm>
#include <memory>
#include <vector>

namespace Logic {
/**
     * @brief Base class for the Observer pattern.
     * Holds a list of listeners (Views) and notifies them when data changes.
 */
class Subject {
private:
    /**
         * @brief List of observers.
         * Uses weak_ptr to prevent circular dependency memory leaks.
     */
    std::vector<std::weak_ptr<Observer>> observers;

public:
    virtual ~Subject() = default;

    void addObserver(std::weak_ptr<Observer> observer) { observers.push_back(observer); }

    // calls update() on all valid observers
    void notify() {
        auto it = observers.begin();
        while (it != observers.end()) {
            if (auto obs = it->lock()) {
                obs->update();
                it++;
            } else {
                it = observers.erase(it);
            }
        }
    }
};
} // namespace Logic

#endif // PACMANGAME_SUBJECT_H
