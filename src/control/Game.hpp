#ifndef GAME_H
#define GAME_H

#include <SFML/Graphics.hpp>
#include <vector>

#include "../view/Layer.hpp"
#include "../model/GameState.hpp"
#include "PlayerController.hpp"
#include "AliensController.hpp"
#include "../view/GameDrawer.hpp"



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

    // updates all game elements
    void update(float time_passed);

    // draws the scene
    void draw();

    void finish();

    void check_alien_hits();

    void check_player_hits();

    bool check_collision(Positionable& s1, Positionable& s2);



    GameState state;

    PlayerController player_controller;
    AliensController aliens_controller;

    sf::RenderWindow window; // unfortunately needed here for start and input (dependence on sfml)

    std::unique_ptr<GameDrawer> drawer;



};

#endif