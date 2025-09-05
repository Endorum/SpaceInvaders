#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include "../model/Constants.hpp"

/**
 * Factory class for creating text objects.
 */
class TextFactory {
public:
    static const sf::Font& get_font() {
        static sf::Font font;
        static bool loaded = false;
        if (!loaded) {
            if (!font.openFromFile(constants::SCORE_FONT_PATH)) {
                std::cerr << "[TextFactory] Failed to load font: " << constants::SCORE_FONT_PATH << std::endl;
            } else {
                loaded = true;
            }
        }
        return font;
    }
    
    /**
     * Create a score text object with the specified parameters.
     * @param initial_text The initial text to display.
     * @param character_size The size of the characters (default is 20).
     * @param pos_x The x position of the text (default is 10.f).
     * @param pos_y The y position of the text (default is 10.f).
     * @return An sf::Text object configured with the specified parameters.
     */
    static sf::Text create_score_text(const std::string& initial_text,
                                      unsigned int character_size = 20,
                                      float pos_x = 10.f,
                                      float pos_y = 10.f) {

        sf::Text text(get_font());
        text.setString(initial_text);
        text.setCharacterSize(character_size);
        text.setFillColor(sf::Color::White);
        text.setStyle(sf::Text::Regular);
        text.setPosition({pos_x, pos_y});
        return text;
    }
};