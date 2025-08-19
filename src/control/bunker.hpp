#pragma once

#include "../model/Constants.hpp"

#include <SFML/Graphics.hpp>
#include <iostream>

class Bunker{
public:
    Bunker( float init_pos_x, float init_pos_y, 
            const sf::Texture& t_full_health, 
            const sf::Texture& t_small_damage, 
            const sf::Texture& t_large_damage, 
            const sf::Texture& t_destroid) : 
            
            pos_x(init_pos_x), pos_y(init_pos_y), sprite(t_full_health),
            texture_small_damage(t_small_damage),
            texture_large_damage(t_large_damage),
            texture_destroid(t_destroid) {

        size = 3;
        sprite.setTexture(t_full_health); // initialized with full health sprite

        health = 4; // 0 = gone, 1 = destroid, 2 = damaged alot, 3 = damaged a little, 4 = full health

        sprite.setOrigin(sf::Vector2f( 16.f, 16.f ));
        sprite.setScale({size, size});
        sprite.setPosition(sf::Vector2f( pos_x, pos_y ));
    }

    const sf::Sprite& get_sprite() const {
        return sprite;
    }

    float get_pos_x() const {return pos_x;}
    float get_pos_y() const {return pos_y;}
    float get_px_size() const { return size*32; }

    void damage(int amount = 1) { health -= amount; }

    // returns true if health <= 0
    // set appropiate textures
    bool update(){  
        switch(health){
            default:
                std::cerr << "Invalid health amount" << std::endl;
                exit(1);

            case 0:
                // make sprite invisable
                return true; 
            case 1:
                sprite.setTexture(texture_destroid);
                return false; 
            case 2:
                sprite.setTexture(texture_large_damage);
                return false;
            case 3:
                sprite.setTexture(texture_small_damage);
                return false;
            case 4: 
                // texture should already be full health, from the constructor
                return false;
            
        }
    }

private:

    float pos_x;
    float pos_y;


    float size;

    int health;

    // const sf::Texture& texture_full_health;
    const sf::Texture& texture_small_damage;
    const sf::Texture& texture_large_damage;
    const sf::Texture& texture_destroid;

    sf::Sprite sprite;
};