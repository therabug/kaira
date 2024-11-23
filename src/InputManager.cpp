#include "InputManager.h"

namespace kaira
{
    /**
     * Checks if a sprite is being hovered over by the mouse cursor.
     *
     * @param sprite The sprite to check for hovering.
     * @param window The window to get the mouse position from.
     * @return True if the sprite is being hovered over, false otherwise.
     */
    bool InputManager::isSpriteHovered(sf::Sprite sprite, sf::RenderWindow& window) {
        // Create a temporary rectangle to represent the sprite's bounds
        sf::IntRect tempRect(sprite.getPosition().x, sprite.getPosition().y, sprite.getGlobalBounds().width, sprite.getGlobalBounds().height);
        
        // Check if the mouse cursor is within the sprite's bounds
        if (tempRect.contains(sf::Mouse::getPosition(window))) {
            return true; // Sprite is being hovered over
        }
        return false; // Sprite is not being hovered over
    }

    /**
     * Checks if a sprite is being clicked by the mouse cursor.
     *
     * @param sprite The sprite to check for clicking.
     * @param button The mouse button to check for clicking.
     * @param window The window to get the mouse position from.
     * @return True if the sprite is being clicked, false otherwise.
     */
    bool InputManager::isSpriteClicked(sf::Sprite sprite, sf::Mouse::Button button, sf::RenderWindow& window) {
        // Check if the mouse button is pressed and the sprite is being hovered over
        if (sf::Mouse::isButtonPressed(button) && isSpriteHovered(sprite, window)) {
            return true; // Sprite is being clicked
        }
        return false; // Sprite is not being clicked
    }

    /**
     * Gets the current mouse position within a window.
     *
     * @param window The window to get the mouse position from.
     * @return The current mouse position as a 2D vector.
     */
    sf::Vector2i InputManager::GetMousePosition(sf::RenderWindow& window) {
        // Get the mouse position from the window
        return sf::Mouse::getPosition(window);
    }
}