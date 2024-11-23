#pragma once

#include <memory>
#include <string>
#include <SFML/Graphics.hpp>

#include "StateMachine.h"
#include "InputManager.h"
#include "AssetManager.h"

namespace kaira {
	struct GameData {
		StateMachine machine;
		sf::RenderWindow window;
		InputManager inputManager;
		AssetManager assets;
	};

	typedef std::shared_ptr<GameData> GameDataRef;

	// Game class with more customizable options
	class Game {
	public:
		/**
		 * Constructor for the Game class.
		 * Initializes the game window with the specified width, height, title,
		 * delta time (for fixed timestep), and max frame time.
		 *
		 * @param width The width of the game window.
		 * @param height The height of the game window.
		 * @param title The title of the game window.
		 * @param dt The fixed delta time for the update step (default: 1/60).
		 * @param maxFrameTime The maximum time allowed for one frame to prevent overuse (default: 0.25f).
		 */
		Game(int width, int height, std::string title, float dt = 1.0f / 60.0f, float maxFrameTime = 0.25f);

		// Getter for game data
		GameDataRef GetData() const { return _data; }

		// Setter to change the fixed time step (delta time)
		void SetFixedTimeStep(float newDt);

		// Setter to change the max frame time
		void SetMaxFrameTime(float newMaxFrameTime);

	private:
		float dt;  // The fixed delta time for updates
		float maxFrameTime;  // The maximum frame time to limit performance spikes

		sf::Clock _clock;
		GameDataRef _data = std::make_shared<GameData>();

		// Main game loop that will be called in the constructor
		void Run();

		// Handles the game events (like window closing)
		void CustomEventHandling();
	};
}
