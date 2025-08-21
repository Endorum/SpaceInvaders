#include "Player.hpp"


#include <SFML/Audio/Sound.hpp>
#include <SFML/Audio/SoundBuffer.hpp>

Player::Player(sf::Texture t, const sf::SoundBuffer& sb) 
    : position(constants::VIEW_WIDTH/2), health(300), width(32), height(32), vert_pos(-40), texture(t), sprite(t), shooting_sound(sb) {

    

    

    int start_pos = constants::VIEW_WIDTH/2;

    sprite.setTexture(texture);


    sprite.setScale({2.f,2.f});
    sprite.setOrigin(sf::Vector2f( width / 2.f, height / 2.f) );
    sprite.setPosition(sf::Vector2f( start_pos, vert_pos ) );
    

    shooting_buffer = sb;
    shooting_sound.setBuffer(shooting_buffer);
    shooting_sound.setVolume(10.f);
}


void Player::update_sprite_position()
{
    sprite.setPosition(sf::Vector2f( position, vert_pos ) );
}

void Player::move_left(int amount){
    position -= amount;

    if(!in_bounds()){
        position += amount;
    }

    update_sprite_position();
} 

void Player::move_right(int amount){
    position += amount;

    if(!in_bounds()){
        position -= amount;
    }

    update_sprite_position();
}

const sf::Sprite& Player::get_sprite() const {
    return sprite;
}

void Player::shoot_laser(){
    Laser* laser = new Laser(position, vert_pos - height/2.f, 5);
    lasers.push_back(laser);


    // play shooting sound
    shooting_sound.play();
}

float Player::get_width() const {
    return width;
}

void Player::decrease_health() {
    health--;
}

float Player::get_height() const {
    return height;
}

int Player::get_health() const {
    return health;
}

// update player, currently only updates the lasers
void Player::update(){
    // check for health etc.


    // Use Iterators so we can erase the laser safely
    for(auto it = lasers.begin(); it != lasers.end(); ){
        Laser* laser = *it;
        bool destroy = laser->move_up();

        if(destroy){
            delete laser;
            it = lasers.erase(it);
        }else it++;
    }
}

void Player::destroy_laser(Laser* laser) {
    if(!laser) return;
    auto it = std::find(lasers.begin(), lasers.end(), laser);
    if (it != lasers.end()) {
        delete *it; // delete the laser object
        lasers.erase(it); // remove from the vector
    }
}

std::vector<Laser*>& Player::get_lasers(){
    return lasers;
}

bool Player::in_bounds(){
    return (
        (position - width/2 >= 0) && /* left side */
        (position + width/2 <= constants::VIEW_WIDTH) /* right side */
    );
}