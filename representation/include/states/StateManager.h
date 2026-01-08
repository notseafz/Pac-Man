
#ifndef PACMANGAME_STATEMANAGER_H
#define PACMANGAME_STATEMANAGER_H

#include "State.h"
#include <memory>
#include <stack>

namespace Representation {
class StateManager {
private:
    std::stack<std::unique_ptr<State>> stateStack;
    std::unique_ptr<State> newState;

    bool isAdding = false;
    bool isReplacing = false;
    bool isRemoving = false;

public:
    StateManager() = default;
    void addState(std::unique_ptr<State> state, bool replace = false);
    void popState();
    void processStateChanges();
    std::unique_ptr<State>& getActiveState();
};
} // namespace Representation
#endif // PACMANGAME_STATEMANAGER_H