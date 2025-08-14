#pragma once

#include "../model/Constants.hpp"
#include <SFML/Graphics.hpp>

class Laser{
public:
    // int id=0;

    // Remove the texture reference default param; use a persistent static texture instead
    Laser(float init_pos_x, float init_pos_y, int init_speed = 1)
        : speed(init_speed),
          pos_x(init_pos_x),
          pos_y(init_pos_y),
          size(1),
          sprite(texture()) // bind to persistent texture
    {
        sprite.setScale({1.f, 1.f});
        sprite.setOrigin({16.f, 16.f});
        sprite.setPosition(sf::Vector2f{pos_x, pos_y});
    }

    void update_sprite_position(){
        sprite.setPosition(sf::Vector2f{pos_x, pos_y});
    }

    const sf::Sprite& get_sprite() const {
        return sprite;
    }    

    float get_pos_x() const { return pos_x; }
    float get_pos_y() const { return pos_y; }

    float get_width() const { return width; }
    float get_height() const { return height; }

    float get_bound_size_x() const { return 3 * size; }
    float get_bound_size_y() const { return 7 * size; }
   
    // return true if out of bounds, so it can be deleted.
    bool move_down(){
        return move(speed);
    }

    bool move_up(){
        return move(-speed);
    }

private:
    bool move(float speed) {
        pos_y += speed;
        update_sprite_position();

        // destroy the laser if its out of bounds
        if(pos_y > constants::VIEW_HEIGHT + 10 || pos_y < -constants::VIEW_HEIGHT){
            return true;
        }
        return false;
    }

    // Persistent, lazily-loaded texture used by all lasers
    static sf::Texture& texture() {
        static sf::Texture tex;
        static bool loaded = false;
        if (!loaded) {
            if (!tex.loadFromFile(constants::LASER_TEXTURE_PATH)) {
                // Failed to load: leave empty texture; SFML will bind none safely.
            }
            loaded = true;
        }
        return tex;
    }

    float speed; // can be tweaked
    float pos_x;
    float pos_y;
    int size;

    float width = 3.f;
    float height = 7.f;

    sf::Sprite sprite;
};


