#pragma once
#include "Positionable.hpp"

class Laser : public Positionable {
public:
    Laser(float x, float y) : x(x), y(y), width(1), height(10) {}

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

private:
    // coordinates
    float x, y;
    // dimensions
    float width, height;

    void set_position(float x, float y) override {
        this->x = x;
        this->y = y;
    }
};
