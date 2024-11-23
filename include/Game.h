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

	class Game {
	public:
		Game(int width, int height, std::string title);

		GameDataRef GetData() const { return _data; }

	private:
		const float dt = 1.0f / 60.0f;
		sf::Clock _clock;

		GameDataRef _data = std::make_shared<GameData>();

		void Run();
	};
}
