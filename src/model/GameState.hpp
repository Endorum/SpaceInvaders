#include "Alien.hpp"
#include "Player.hpp"
#include "Laser.hpp"
#pragma once


class GameState {
public:
    GameState() : player(constants::VIEW_WIDTH / 2, constants::VIEW_HEIGHT - 200), aliens() {
    }
    void update();

    std::vector<Alien>& get_aliens() {
        return aliens;
    }

    bool& get_alien_direction_right() {
        return alien_direction_right;
    }

    float& get_alien_speed() {
        return alien_speed;
    }

    Player& get_player() {
        return player;
    }

    void add_alien(const Alien& alien) {
        aliens.push_back(alien);
    }

    void set_alien_direction_right(bool direction) {
        alien_direction_right = direction;
    }

private:
    Player player;
    std::vector<Alien> aliens;
    float alien_speed = constants::ALIEN_SPEED;
    bool alien_direction_right = true;
};
