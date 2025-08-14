#ifndef GAME_H
#define GAME_H

#include <SFML/Graphics.hpp>
#include <vector>

#include "../view/Layer.hpp"
#include "Score.hpp"
#include "Player.hpp"
#include "Alien.hpp"



// Game class
class Game {

public:
    //initialize the game (window and controls)
    Game();

    // start the game
    void start();



private:
    // processes user input, returns true if window has been closed
    bool input();
    void place_aliens(int amount, sf::Texture& texture, int rows = 5, int elms = 10);
    void processInput();

    // updates all game elements
    void update(float time_passed);

    // draws the scene
    void draw();

    void finish();

    sf::RenderWindow window;

    void show_lasers();
    void add_aliens_to_layer();

    void check_alien_hits();

    void move_aliens(float time_passed);

    // view area and layers
    sf::View view;
    Layer game_layer;

    Player* player;

    std::vector<Alien> aliens;

    float alien_speed = constants::ALIEN_SPEED;

    bool alien_direction_right = true;

    Score score;

};

#endif