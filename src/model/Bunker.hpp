#pragma once

#include "../model/Constants.hpp"

#include <SFML/Graphics.hpp>
#include <iostream>

class Bunker : public Positionable {
public:
    Bunker( float x, float y) : x(x), y(y), width(constants::BUNKER_WIDTH), height(constants::BUNKER_HEIGHT), health(constants::BUNKER_HEALTH) {

    }

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
    float get_px_size() const { return width * 32; }

    int get_health() const {
        return health;
    }

    void set_health(int h) {
        health = h;
        if(health < 0) health = 0;
        if(health > 10) health = 10;
    }

    void set_position(float new_x, float new_y) override {
        x = new_x;
        y = new_y;
    }

private:

    float x, y;
    float width, height;

    int health;
};