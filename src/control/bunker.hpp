#pragma once

#include "../model/Constants.hpp"

#include <SFML/Graphics.hpp>
#include <iostream>

class Bunker{
public:
    Bunker( float init_pos_x, float init_pos_y, 
            const sf::Texture* t_full_health, 
            const sf::Texture* t_small_damage, 
            const sf::Texture* t_large_damage, 
            const sf::Texture* t_destroid) : 
            
            pos_x(init_pos_x), pos_y(init_pos_y), 
            texture_small_damage(t_small_damage),
            texture_large_damage(t_large_damage),
            texture_destroid(t_destroid),
            sprite(*t_full_health), {

        size = 2;
        sprite.setTexture(*t_full_health); // initialized with full health sprite

        // 0    : gone
        // 1-2  : texture_destroid
        // 3-5  : texture_large_damage
        // 6-8  : texture_small_damage
        // 9-10 : t_full_health
        health = 10;

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

        if(health <= 0){
            // make sprite invisable
            sprite.setColor({0,0,0,255});
            return true; 
        }
        if(health <= 2){
            sprite.setTexture(*texture_destroid);
            return false; 
        }
        if(health <= 5){
            sprite.setTexture(*texture_large_damage);
            return false; 
        }
        if(health <= 8){
            sprite.setTexture(*texture_small_damage);
            return false; 
        }else{
            // do nothing the texture should be at full health
        }

        return false;
    }

private:

    float pos_x;
    float pos_y;


    float size;

    int health;

    // const sf::Texture* texture_full_health;
    const sf::Texture* texture_small_damage;
    const sf::Texture* texture_large_damage;
    const sf::Texture* texture_destroid;

    sf::Sprite sprite;
};