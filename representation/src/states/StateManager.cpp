#include "states/StateManager.h"

namespace Representation {
    void StateManager::addState(std::unique_ptr<State> state, bool replace) {
        this->isAdding = true;
        this->isReplacing = replace;
        this->newState = std::move(state);
    }

    void StateManager::popState() {
        this->isRemoving = true;
    }

    void StateManager::processStateChanges() {
        if (isRemoving && !stateStack.empty()) {
            stateStack.pop();
            if (!stateStack.empty()) stateStack.top()->resume();
            isRemoving = false;
        }

        if (isAdding) {
            if (!stateStack.empty()) {
                if (isReplacing) stateStack.pop();
                else stateStack.top()->pause();
            }
            stateStack.push(std::move(newState));
            stateStack.top()->init();
            isAdding = false;
        }
    }

    std::unique_ptr<State>& StateManager::getActiveState() {
        return stateStack.top();
    }
}