#include "StateMachine.h"

namespace kaira
{
    /**
     * @brief Adds a new state to the state machine.
     * 
     * @param newState The state to be added.
     * @param isReplacing Whether to replace the current state or not.
     */
    void StateMachine::AddState(StateRef newState, bool isReplacing)
    {
        this->_isAdding = true; // Set the adding flag to true
        this->_isReplacing = isReplacing; // Set the replacing flag to the passed value

        this->_newState = std::move(newState); // Move the new state into the state machine
    }

    /**
     * @brief Removes the current state from the state machine.
     */
    void StateMachine::RemoveState()
    {
        this->_isRemoving = true; // Set the removing flag to true
    }

    /**
     * @brief Processes any state changes that have been requested.
     * 
     * This function checks if a state has been requested to be removed or added,
     * and performs the necessary actions accordingly.
     */
    void StateMachine::ProcessStateChanges()
    {
        if (this->_isRemoving && !this->_states.empty()) // If a state is being removed and there are states in the stack
        {
            this->_states.pop(); // Remove the top state from the stack

            if (!this->_states.empty()) // If there are still states in the stack
            {
                this->_states.top()->Resume(); // Resume the new top state
            }

            this->_isRemoving = false; // Reset the removing flag
        }

        if (this->_isAdding) // If a state is being added
        {
            if (!this->_states.empty()) // If there are states in the stack
            {
                if (this->_isReplacing) // If the new state is being added to replace the current state
                {
                    this->_states.pop(); // Remove the current state from the stack
                }
                else
                {
                    this->_states.top()->Pause(); // Pause the current state
                }
            }

            this->_states.push(std::move(this->_newState)); // Add the new state to the stack
            this->_states.top()->Init(); // Initialize the new state
            this->_isAdding = false; // Reset the adding flag
        }
    }

    /**
     * @brief Returns a reference to the currently active state.
     * 
     * @throws std::runtime_error If there are no states in the state machine.
     * @return StateRef& The reference to the currently active state.
     */
    StateRef& StateMachine::GetActiveState()
    {
        if (this->_states.empty()) // If there are no states in the state machine
        {
            throw std::runtime_error("StateMachine: No active state! Make sure to add a state before starting."); // Throw an error
        }

        return this->_states.top(); // Return a reference to the top state in the stack
    }
}