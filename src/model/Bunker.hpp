#pragma once

#include "../model/Constants.hpp"

#include <SFML/Graphics.hpp>
#include <iostream>
#include "Positionable.hpp"

class Bunker : public Positionable {
public:
    Bunker( float x, float y) : x(x), y(y), width(constants::BUNKER_WIDTH), height(constants::BUNKER_HEIGHT), health(constants::BUNKER_HEALTH) {}

    // Positionable interface
    float get_pos_x() const override {
        return x;
    }
    float get_pos_y() const override {
        return y;
    }
    float get_width() const override {
        return width;
    }
    float get_height() const override {
        return height;
    }

    int get_health() const {
        return health;
    }

    /**
     * Set the health of the bunker.
     */
    void set_health(int h) {
        health = h;
        if(health < 0) health = 0;
        if(health > 10) health = 10;
    }

    /**
     * Set the position of the bunker.
     */
    void set_position(float new_x, float new_y) override {
        x = new_x;
        y = new_y;
    }

private:
    // coordinates
    float x, y;
    // dimensions
    float width, height;
    // health of the bunker (0-10)
    int health;
};