#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include "../model/Constants.hpp"

class TextFactory {
public:
    static const sf::Font& get_font() {
        static sf::Font font;
        static bool loaded = []{
            if (!font.openFromFile(constants::SCORE_FONT_PATH)) {
                std::cerr << "Could not load score font: " << constants::SCORE_FONT_PATH << std::endl;
                return false;
            }
            return true;
        }();
        (void)loaded;
        return font;
    }

    static sf::Text create_score_text(const std::string& initial_text,
                                      unsigned int character_size = 20,
                                      float pos_x = 10,
                                      float pos_y = -constants::VIEW_HEIGHT + 30) {
        sf::Text text = sf::Text(get_font());
        text.setString(initial_text);
        text.setCharacterSize(character_size);
        text.setFillColor(sf::Color::White);
        text.setStyle(sf::Text::Regular);
        text.setPosition({pos_x, pos_y});
        return text;
    }
};