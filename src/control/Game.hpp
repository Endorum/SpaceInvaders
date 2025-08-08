#ifndef GAME_H
#define GAME_H

#include <SFML/Graphics.hpp>
#include <vector>

#include "../view/Layer.hpp"
#include "Player.hpp"
#include "alien.hpp"



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

    sf::RenderWindow window;

    void show_lasers();
    void add_aliens_to_layer();

    // view area and layers
    sf::View view;
    Layer game_layer;

    Player* player;

    std::vector<Alien> aliens;

};

#endif