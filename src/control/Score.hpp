#ifndef SCORE_HPP
#define SCORE_HPP

#include <SFML/Graphics.hpp>

class Score {
public:
    explicit Score(int s);

    const sf::Drawable& get_text();

    // Increase the score and update the text
    void increase(int amount);

private:
    void update_text();

    int score;

    sf::Text text;
};

#endif // SCORE_HPP