#pragma once

#include "../model/Constants.hpp"

#include <SFML/Graphics.hpp>

class Alien{

public:
    Alien(float init_pos_x, float init_pos_y, const sf::Texture& t) : pos_x(init_pos_x), pos_y(init_pos_y), sprite(t) {

        size = 3; // default size of alien sprite
        sprite.setTexture(t);

        sprite.setOrigin(sf::Vector2f( 16.f, 16.f ));
        sprite.setScale({size, size});
        sprite.setPosition(sf::Vector2f( pos_x, pos_y ));

    }


    void update_sprite_position(){
        sprite.setPosition(sf::Vector2f( pos_x, pos_y ));
    }

    const sf::Sprite& get_sprite() const {
        return sprite;
    }

    bool in_bounds_vertical(){
        return (
            pos_y < -100
        );
    }
    

    float get_pos_x() const {return pos_x;}
    float get_pos_y() const {return pos_y;}

    float get_px_size() const { return size*32; } // sprite is 32x32 px

    float get_bound_size_x() const { return 14 * size; }
    float get_bound_size_y() const { return 9 * size; }


    bool in_bounds(){
        float half_bound_size = get_bound_size_x() /2;
        return 
            pos_x >= half_bound_size && pos_x < constants::VIEW_WIDTH - half_bound_size;
    }

    // amount <= 0 -> to the left, amount >= 0 -> to the right
    void move_vertically(int amount){
        pos_y += amount;

        update_sprite_position();
    }

    std::vector<Laser*>& get_lasers() {
        return lasers;
    }

    // amount <= 0 -> up, amount >= 0 -> down
    void move_horizontally(int amount){
        pos_x += amount;

        update_sprite_position();
    }

    void shoot_laser() {
        Laser* laser = new Laser(pos_x, pos_y + get_bound_size_y() / 2.f, 5);
        lasers.push_back(laser);
    }

    void destroy_laser(Laser* laser) {
        auto it = std::find(lasers.begin(), lasers.end(), laser);
        if (it != lasers.end()) {
            delete *it; // delete the laser object
            lasers.erase(it); // remove from the vector
        }

    }

    void update(){
        for(auto it = lasers.begin(); it != lasers.end(); ){
            Laser* laser = *it;
            bool destroy = laser->move_down();

            if(destroy){
                delete laser;
                it = lasers.erase(it);
            }else it++;
        }
    }


private:
    float pos_x;
    float pos_y;

    std::vector<Laser*> lasers;


    // assuming aliens are square and not rectangular
    float size; 

    // aliens only need one hit to die
    bool alive = true;

    // TODO: think about how many points a kill yields
    int yielding_points = 0;

    sf::Sprite sprite;

}; 