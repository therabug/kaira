#include "Game.h"

namespace kaira
{
    /**
     * Constructor for the Game class.
     * Initializes the game window with the specified width, height, and title.
     * 
     * @param width The width of the game window.
     * @param height The height of the game window.
     * @param title The title of the game window.
     */
    Game::Game(int width, int height, std::string title) {
        // Check if the game data is already initialized
        if (_data) {
            // Create the game window with the specified dimensions and title
            _data->window.create(sf::VideoMode(width, height), title, sf::Style::Close | sf::Style::Titlebar);
        }

        // Start the game loop
        this->Run();
    }

    /**
     * The main game loop.
     * Handles the game's logic, input, and rendering.
     */
    void Game::Run() {
        // Variables to keep track of time
        float newTime, frameTime, interpolation;

        // Get the current time
        float currentTime = this->_clock.getElapsedTime().asSeconds();
        // Initialize the accumulator for fixed time step
        float accumulator = 0.0f;

        // Game loop
        while (this->_data->window.isOpen()) {
            // Process any state changes in the state machine
            this->_data->machine.ProcessStateChanges();

            // Calculate the time elapsed since the last frame
            newTime = this->_clock.getElapsedTime().asSeconds();
            frameTime = newTime - currentTime;

            // Limit the frame time to prevent excessive CPU usage
            if (frameTime > 0.25f) {
                frameTime = 0.25f;
            }

            // Update the current time
            currentTime = newTime;
            // Add the frame time to the accumulator
            accumulator += frameTime;

            // Fixed time step loop
            while (accumulator >= dt) {
                // Handle input for the current state
                this->_data->machine.GetActiveState()->HandleInput();
                // Update the current state
                this->_data->machine.GetActiveState()->Update(dt);

                // Subtract the fixed time step from the accumulator
                accumulator -= dt;
            }

            // Calculate the interpolation factor for smooth rendering
            interpolation = accumulator / dt;
            // Draw the current state with interpolation
            this->_data->machine.GetActiveState()->Draw(interpolation);
        }
    }
}