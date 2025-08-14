#include "Score.hpp"

#include <stdexcept>
#include "../model/Constants.hpp"

Score::Score(int s) : score(s), font("assets/fonts/dejavu.ttf"), text(font) {
    text.setCharacterSize(20);
    text.setStyle(sf::Text::Regular);
    if (s < 0) {
        throw std::invalid_argument("Score cannot be negative");
    }
    text.setString("Score: " + std::to_string(score));
    text.setPosition({10, -constants::VIEW_HEIGHT + 10.f}); // Set position of the text
    text.setScale({1.0f, 1.0f});
    text.setFillColor(sf::Color::White); // Set text color
}

const sf::Drawable& Score::get_text()
{
    return text;
}

void Score::increase(int amount) {
    score += amount;
    update_text();
}

void Score::update_text() {
    text.setString("Score: " + std::to_string(score));
}
