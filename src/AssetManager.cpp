#include "AssetManager.h"

namespace kaira
{
    /**
     * Loads a texture from a file and stores it in the asset manager.
     * 
     * @param name The name of the texture to load.
     * @param fileName The file path of the texture to load.
     */
    void AssetManager::LoadTexture(std::string name, std::string fileName)
    {
        // Create a new sf::Texture object
        sf::Texture tex;

        // Attempt to load the texture from the file
        if (tex.loadFromFile(fileName))
        {
            // If the load is successful, add the texture to the asset manager
            this->textures[name] = tex;
        }
    }

    /**
     * Retrieves a texture from the asset manager by name.
     * 
     * @param name The name of the texture to retrieve.
     * @return A reference to the sf::Texture object.
     */
    sf::Texture &AssetManager::GetTexture(std::string name)
    {
        // Return a reference to the texture from the asset manager
        return this->textures.at(name);
    }

    /**
     * Loads a font from a file and stores it in the asset manager.
     * 
     * @param name The name of the font to load.
     * @param fileName The file path of the font to load.
     */
    void AssetManager::LoadFont(std::string name, std::string fileName)
    {
        // Create a new sf::Font object
        sf::Font font;

        // Attempt to load the font from the file
        if (font.loadFromFile(fileName))
        {
            // If the load is successful, add the font to the asset manager
            this->fonts[name] = font;
        }
    }

    /**
     * Retrieves a font from the asset manager by name.
     * 
     * @param name The name of the font to retrieve.
     * @return A reference to the sf::Font object.
     */
    sf::Font &AssetManager::GetFont(std::string name) {
        // Return a reference to the font from the asset manager
        return this->fonts.at(name);
    }
}