
#ifndef PACMANGAME_SUBJECT_H
#define PACMANGAME_SUBJECT_H

#include <vector>
#include <memory>
#include <algorithm>
#include "Observer.h"

namespace Logic {
    class Subject {
    private:
        std::vector<std::weak_ptr<Observer>> observers;

    public:
        virtual ~Subject() = default;

        void addObserver(std::weak_ptr<Observer> observer) {
            observers.push_back(observer);
        }

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
}


#endif //PACMANGAME_SUBJECT_H
