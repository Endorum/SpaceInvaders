#pragma once

#include "../model/Constants.hpp"
#include "../model/Player.hpp"
#include "../model/Laser.hpp"

class PlayerController {
public:
    PlayerController(Player& player);

    /**
     * Move the player left.
     */
    void move_left();

    /**
     * Move the player right.
     */
    void move_right();

    /**
     * Make the player shoot a laser.
     */
    void shoot_laser();

    /**
     * Decrease the player's health.
     */
    void decrease_health();

    /**
     * Destroy the laser at the specified index.
     * @param index The index of the laser to destroy.
     */
    void destroy_laser_at(size_t index);

    /**
     * Increase the player's score by the specified amount.
     * @param amount The amount to increase the score by.
     */
    void increase_score(int amount);

    /**
     * Update the player's state, including moving its lasers.
     * @return true if any laser was removed, false otherwise.
     */
    bool update(float);
private:
    Player& model;
};