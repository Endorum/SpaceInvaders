#pragma once

#include "../model/Constants.hpp"

#include <SFML/Graphics.hpp>

class Alien{

public:
    Alien(float init_pos_x, float init_pos_y, const sf::Texture& t) : pos_x(init_pos_x), pos_y(init_pos_y), sprite(t) {

        size = 3; // default size of alien sprite
        sprite.setTexture(t);

        sprite.setScale({3.f, 3.f});
        sprite.setOrigin(sf::Vector2f( size/2.f, size/2.f ));
        sprite.setPosition(sf::Vector2f( pos_x, pos_y ));

    }


    void update_sprite_position(){
        sprite.setPosition(sf::Vector2f( pos_x, pos_y ));
    }

    const sf::Sprite& get_sprite() const {
        return sprite;
    }

    int get_pos_x() const {return pos_x;}
    int get_pos_y() const {return pos_y;}

    int get_px_size() const { return size*32; } // sprite is 32x32 px


    bool in_bounds(){
        return (
            (pos_x - size/2 >= 0) && /* left side */
            (pos_x + size/2 <= constants::VIEW_WIDTH) && /* right side */
            (pos_y - size/2 >= 0) && /* top side */
            (pos_y + size/2 <= constants::VIEW_HEIGHT) /* bottom side */
        );
    }

    // amount <= 0 -> to the left, amount >= 0 -> to the right
    void move_vertically(int amount){
        pos_x += amount;

        // set position back if out of bounds
        if(!in_bounds()) {
            pos_x -= amount;
        }
    }

    // amount <= 0 -> up, amount >= 0 -> down
    void move_horizontally(int amount){
        pos_y += amount;

        // set position back if out of bounds
        if(!in_bounds()){
            pos_y -= amount;
        }
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