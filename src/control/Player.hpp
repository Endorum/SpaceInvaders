#pragma once

#include "../model/Constants.hpp"

#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/Shape.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics.hpp>

#include <iostream>
#include "Laser.hpp"

#define PLAYER_SPEED 5

class Player{
public:
    Player(sf::Texture t) ;

    void update_sprite_position();

    void move_left(int amount=PLAYER_SPEED);

    void move_right(int amount=PLAYER_SPEED);


    const sf::Sprite& get_sprite() const;


    void shoot_laser();

    float get_width() const;

    void decrease_health();

    float get_height() const;

    int get_health() const;

    void update();

    std::vector<Laser*>& get_lasers();

private:

    // 3 hp at the start, -1 if hit, dead if health <= 0
    int health;

    // in pixels
    int width;
    int height;

    bool in_bounds();



    

    // in the center (+/- width/2 to both sides)
    int position;

    // fixed height
    const int vert_pos;
 
    
    sf::Sprite sprite;
    sf::Texture texture;

    std::vector<Laser*> lasers; // int id for deletion

};  