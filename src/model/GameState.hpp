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

    /**
     * Add a new alien to the game state.
     */
    void add_alien(const Alien& alien) {
        aliens.push_back(alien);
    }

    /**
     * Set the direction of alien movement (true for right, false for left).
     */
    void set_alien_direction_right(bool direction) {
        alien_direction_right = direction;
    }

    void set_level(int new_level) {
        level = new_level;
        alien_speed = constants::ALIEN_SPEED + (level - 1) * constants::ACCELERATION;
    }

private:
    // the player of the game with health and score
    Player player;
    // list of aliens
    std::vector<Alien> aliens;
    // list of bunkers (shields to protect the player from alien lasers)
    std::vector<Bunker> bunkers;
    // current speed of alien movement
    float alien_speed = constants::ALIEN_SPEED;
    // current direction of alien movement (true for right, false for left)
    bool alien_direction_right = true;
    // current game level
    int level = 1;
};
