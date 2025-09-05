#pragma once

#include <vector>
#include "../model/Bunker.hpp"

/**
 * Controller for managing the bunkers.
 */
class BunkersController {
public:
    BunkersController(std::vector<Bunker>& bunkers);

    /**
     * Place a specified number of bunkers evenly spaced at the bottom of the screen.
     * @param amount The number of bunkers to place.
     */
    void place_bunkers(int amount);

    /**
     * Damage the bunker at the specified index by the given amount.
     * @param index The index of the bunker to damage.
     * @param amount The amount of damage to make (default is 1).
     */
    void damage_bunker(size_t index, int amount = 1);
private:
    std::vector<Bunker>& bunkers;
};