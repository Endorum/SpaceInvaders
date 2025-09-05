#pragma once

#include "../model/Constants.hpp"

#include <SFML/Graphics.hpp>
#include "../model/Alien.hpp"

/**
 * Controller for managing a single alien.
 */
class AlienController{

public:
    AlienController(Alien& alien);

    /**
     * Make the alien shoot a laser.
     */
    void shoot_laser();

    /**
     * Destroy the laser at the specified index.
     * @param index The index of the laser to destroy.
     */
    void destroy_laser_at(size_t index);

    /**
     * Move the alien horizontally by dx.
     * @param dx The distance to move the alien.
     * @return true if the alien is out of bounds after the move, false otherwise.
     */
    bool move_horizontal(float dx);

    /**
     * Move the alien vertically by dy.
     * @param dy The distance to move the alien.
     * @return true if the alien is out of bounds after the move, false otherwise.
     */
    bool move_vertical(float dy);
    
    /**
     * Update the alien's state, including moving its lasers.
     */
    void update();

private:
    Alien& model;
};