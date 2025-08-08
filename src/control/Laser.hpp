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

    int get_pos_x() const {return pos_x;}
    int get_pos_y() const {return pos_y;}

   

    // return true if out of bounds, so it can be deleted.
    bool update(){
        pos_y -= speed;

        update_sprite_position();


        if(pos_y > constants::VIEW_HEIGHT + 10){
            return true;
        }

        return false;
    }

private:


    float speed; // can be tweaked

    float pos_x;
    float pos_y;

    int size;

    

    

    sf::Sprite sprite;

};


