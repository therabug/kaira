#pragma once

#include <SFML/Graphics.hpp>

namespace kaira
{
	class InputManager {
	public:
		InputManager() {}
		~InputManager() {}

		bool isSpriteClicked(sf::Sprite sprite, sf::Mouse::Button button, sf::RenderWindow& window);
		bool isSpriteHovered(sf::Sprite sprite, sf::RenderWindow& window);

		sf::Vector2i GetMousePosition(sf::RenderWindow& window);
	};
}