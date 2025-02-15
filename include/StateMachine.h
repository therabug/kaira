#pragma once

#include <memory>
#include <stack>
#include <iostream>
#include "State.h"

namespace kaira {

    typedef std::unique_ptr<State> StateRef;

    class StateMachine
    {
    public:
        StateMachine()
            : _isRemoving(false), _isAdding(false), _isReplacing(false)
        {
        }

        ~StateMachine() {}

        void AddState(StateRef newState, bool isReplacing = true);
        void RemoveState();

        void ProcessStateChanges();

        StateRef& GetActiveState();

    private:
        std::stack<StateRef> _states;
        StateRef _newState;

        bool _isRemoving = false;
        bool _isAdding = false;
        bool _isReplacing = false;
    };

}
