#pragma once

#include "../model/Constants.hpp"
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/Shape.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics.hpp>

#define PLAYER_SPEED 5

class Player{
public:
    Player(int start_pos=constants::VIEW_WIDTH/2) 
        : position(start_pos), health(3), width(20), height(10), vert_pos(-40) {

        shape.setSize(sf::Vector2f(width, height));
        shape.setOrigin(sf::Vector2f( width / 2.f, height / 2.f) );
        shape.setFillColor(sf::Color::Green);
        shape.setPosition(sf::Vector2f( start_pos, vert_pos ) );

    }
    

    void update_shape_position(){
        shape.setPosition(sf::Vector2f( position, vert_pos ) );
    }

    void move_left(int amount=PLAYER_SPEED){
        position -= amount;

        if(!in_bounds()){
            position += amount;
        }

        update_shape_position();
    } 

    void move_right(int amount=PLAYER_SPEED){
        position += amount;

        if(!in_bounds()){
            position -= amount;
        }

        update_shape_position();
    }

    const sf::Sprite& get_sprite() const {

    }

    const sf::RectangleShape& get_shape() const {
        return shape;
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


    sf::RectangleShape shape;
    
    
    sf::Sprite sprite;

};  