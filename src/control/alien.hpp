#pragma once

#include "../model/Constants.hpp"

#include <SFML/Graphics.hpp>

class Alien{

public:
    Alien(float init_pos_x, float init_pos_y, const sf::Texture& t) : pos_x(init_pos_x), pos_y(init_pos_y), sprite(t) {

        size = 3; // default size of alien sprite
        sprite.setTexture(t);

        sprite.setScale({3.f, 3.f});
        sprite.setOrigin(sf::Vector2f( size/2.f, 0));
        sprite.setPosition(sf::Vector2f( pos_x, pos_y ));

    }


    void update_sprite_position(){
        sprite.setPosition(sf::Vector2f( pos_x, pos_y ));
    }

    const sf::Sprite& get_sprite() const {
        return sprite; // Always return the sprite, check alive status separately
    }

    bool is_alive() const {
        return alive;
    }

    void kill() {
        alive = false;
    }



    bool in_bounds(){
        return (
            pos_x >= 0 && pos_x < constants::VIEW_WIDTH - constants::ALIEN_SPACING_X - 10
        );
    }

    bool in_bounds_vertical(){
        return (
            pos_y < -100
        );
    }

    // amount <= 0 -> to the left, amount >= 0 -> to the right
    void move_vertically(float amount){
        pos_y += amount;
        update_sprite_position(); 
    }
    void move_horizontally(float amount){
        pos_x += amount;
        update_sprite_position(); 
    }


private:
    float pos_x;
    float pos_y;


    // assuming aliens are square and not rectangular
    float size; 

    // aliens only need one hit to die
    bool alive = true;

    // TODO: think about how many points a kill yields
    int yielding_points = 0;

    sf::Sprite sprite;

}; 