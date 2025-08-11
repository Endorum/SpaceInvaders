#pragma once


#include "../model/Constants.hpp"



class Laser{
public:

    // int id=0;

    Laser(float init_pos_x, float init_pos_y, const sf::Texture& t, int init_speed = 1) : pos_x(init_pos_x), pos_y(init_pos_y), sprite(t), speed(init_speed) {


        size = 1; // default size for the laser, can be tweaked
        sprite.setTexture(t);

        sprite.setScale({1.f, 1.f}); // can be tweaked
        sprite.setOrigin({16.f,16.f}); // just using the middle of the texture, and as the texture is 32/32 the middle is apporx 16,16
        sprite.setPosition(sf::Vector2f{pos_x, pos_y});

    }

    void update_sprite_position(){
        sprite.setPosition(sf::Vector2f{pos_x, pos_y});
    }

    const sf::Sprite& get_sprite() const {
        return sprite;
    }    

    float get_pos_x() const {return pos_x;}
    float get_pos_y() const {return pos_y;}

    float get_width() const { return width; }
    float get_height() const { return height; }

    float get_bound_size_x() const { return 3 * size; }
    float get_bound_size_y() const { return 7 * size; }
   

    // return true if out of bounds, so it can be deleted.
    bool update(){
        pos_y -= speed;

        update_sprite_position();


        // destroy the laser if its out of bounds
        if(pos_y > constants::VIEW_HEIGHT + 10 || pos_y < -constants::VIEW_HEIGHT){
            return true;
        }

        return false;
    }

private:


    float speed; // can be tweaked

    float pos_x;
    float pos_y;

    int size;

    float width = 3.f;
    float height = 7.f;

    

    sf::Sprite sprite;

};


