#pragma once

#include "../model/Constants.hpp"

#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/Shape.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics.hpp>

#include <iostream>

#define PLAYER_SPEED 5

class Player{
public:
    Player(sf::Texture t) 
        : position(constants::VIEW_WIDTH/2), health(3), width(32), height(32), vert_pos(-40), texture(t),  sprite(t) {

        


        int start_pos = constants::VIEW_WIDTH/2;

        sprite.setTexture(texture);


        sprite.setScale({2.f,2.f});
        sprite.setOrigin(sf::Vector2f( width / 2.f, height / 2.f) );
        sprite.setPosition(sf::Vector2f( start_pos, vert_pos ) );
        

    }

    void update_sprite_position(){
        sprite.setPosition(sf::Vector2f( position, vert_pos ) );
    }

    void move_left(int amount=PLAYER_SPEED){
        position -= amount;

        if(!in_bounds()){
            position += amount;
        }

        update_sprite_position();
    } 

    void move_right(int amount=PLAYER_SPEED){
        position += amount;

        if(!in_bounds()){
            position -= amount;
        }

        update_sprite_position();
    }


    const sf::Sprite& get_sprite() const {
        return sprite;
    }

private:

    // 3 hp at the start, -1 if hit, dead if health <= 0
    int health;

    // in pixels
    int width;
    int height;

    bool in_bounds(){
        return (
            (position - width/2 >= 0) && /* left side */
            (position + width/2 <= constants::VIEW_WIDTH) /* right side */
        );
    }

    

    // in the center (+/- width/2 to both sides)
    int position;

    // fixed height
    const int vert_pos;
 
    
    sf::Sprite sprite;
    sf::Texture texture;

};  