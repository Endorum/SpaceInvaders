#ifndef GAME_H
#define GAME_H

#include <SFML/Graphics.hpp>
#include <vector>

#include "../view/Layer.hpp"
#include "Player.hpp"
#include "Alien.hpp"
// Forward declaration to avoid circular include




// Game class
class Game {

public:
    //initialize the game (window and controls)
    Game();

    // start the game
    void start();

    // 5 rows x 10 elms 
    void place_aliens(int amount, sf::Texture* texture, int rows=5, int elms=10){

        // int x_pos = 0;
        // int y_pos = 0;

        // int gap = 1; // in px

        // for(int i=0;i<amount;i++){

        //     x_pos += 1;
            
        //     if(i % elms == 0){
        //         x_pos = 0;
        //         y_pos += 1;
        //     }


        //     Alien alien(x_pos,y_pos,texture);

        //     aliens.push_back(alien);
        // }
    }

    void add_aliens_to_layer(){
        // for(int i=0;i<aliens.size();i++){
        //     game_layer.add_to_layer(aliens.at(i).get_sprite());
        // }
    }

private:
    // processes user input, returns true if window has been closed
    bool input();
    void processInput();

    // updates all game elements
    void update(float time_passed);

    // draws the scene
    void draw();

    sf::RenderWindow window;

    // view area and layers
    sf::View view;
    Layer game_layer;

    
    Player* player;
    
    Alien* alien;

};

#endif