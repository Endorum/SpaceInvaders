#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include "../model/Constants.hpp"

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