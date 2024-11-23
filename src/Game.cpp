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
     * @param dt The fixed time step used for updates.
     * @param maxFrameTime The maximum frame time allowed to prevent excessive CPU usage.
     */
    Game::Game(int width, int height, std::string title, float dt, float maxFrameTime)
        : dt(dt), maxFrameTime(maxFrameTime)
    {
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
    void Game::Run()
    {
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
            if (frameTime > maxFrameTime) {
                frameTime = maxFrameTime;
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

            // Optional: Handle custom events or additional actions in the game loop
            CustomEventHandling();
        }
    }

    /**
     * Allows for custom event handling or additional game loop behavior.
     * Can be overridden or extended by subclasses or users to implement custom logic.
     */
    void Game::CustomEventHandling()
    {
        // Example: process window events (like close or resize)
        sf::Event event;
        while (this->_data->window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                this->_data->window.close();
            }
        }
    }

    /**
     * Set a custom time step for fixed updates.
     *
     * @param newDt The new time step value.
     */
    void Game::SetFixedTimeStep(float newDt)
    {
        dt = newDt;
    }

    /**
     * Set the maximum frame time.
     *
     * @param newMaxFrameTime The new maximum frame time value.
     */
    void Game::SetMaxFrameTime(float newMaxFrameTime)
    {
        maxFrameTime = newMaxFrameTime;
    }
}
