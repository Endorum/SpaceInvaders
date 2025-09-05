#pragma once

#include <vector>
#include "../model/Alien.hpp"
#include "AlienController.hpp"
#include "RandomUtils.hpp"

/**
 * Controller for managing the aliens.
 */
class AliensController {
public:
    AliensController(std::vector<Alien>& aliens, bool& alien_direction_right, float& alien_speed);

    /**
     * Update the state of all aliens (movement, shooting).
     * @param time_passed The time passed since the last update in seconds.
     * @return true if any alien moved out of bounds, false otherwise.
     */
    bool update(float time_passed);

    /**
     * Place a specified number of aliens in a grid formation.
     * @param amount The total number of aliens to place.
     * @param rows The number of rows in the grid.
     * @param elms The number of columns in the grid.
     */
    void place_aliens(int amount, int rows = 5, int elms = 10);

    /**
     * Destroy the laser at the specified index for the given alien.
     * @param alien The alien whose laser is to be destroyed.
     * @param index The index of the laser to destroy.
     */
    void destroy_laser_at(Alien& alien, size_t index);
private:
    bool move_aliens(float time_passed);
    std::vector<Alien>& aliens;
    bool& alien_direction_right;
    float& alien_speed;
};