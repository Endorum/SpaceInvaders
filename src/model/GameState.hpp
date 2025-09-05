#include "Alien.hpp"
#include "Player.hpp"
#include "Laser.hpp"
#include "Bunker.hpp"
#pragma once


class GameState {
public:
    GameState() : player(constants::VIEW_WIDTH / 2, constants::VIEW_HEIGHT - 50), aliens() {
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

    int get_level() const {
        return level;
    }

    std::vector<Bunker>& get_bunkers() {
        return bunkers;
    }

    void add_alien(const Alien& alien) {
        aliens.push_back(alien);
    }

    void set_alien_direction_right(bool direction) {
        alien_direction_right = direction;
    }

    void set_level(int new_level) {
        level = new_level;
        alien_speed = constants::ALIEN_SPEED + (level - 1) * constants::ACCELERATION;
    }

private:
    Player player;
    std::vector<Alien> aliens;
    std::vector<Bunker> bunkers;
    float alien_speed = constants::ALIEN_SPEED;
    bool alien_direction_right = true;
    int level = 1;
};
