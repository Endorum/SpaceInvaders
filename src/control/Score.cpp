#include "Score.hpp"

#include <stdexcept>
#include "../model/Constants.hpp"
#include "TextFactory.hpp"

Score::Score(int s) : score(s), text(TextFactory::create_score_text("Score: " + std::to_string(s))) {
    if (s < 0) {
        throw std::invalid_argument("Score cannot be negative");
    }
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
