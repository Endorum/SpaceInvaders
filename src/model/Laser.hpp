#pragma once
#include "Positionable.hpp"

class Laser : public Positionable {
public:
    Laser(float x, float y, float w=1, float h=10) : x(x), y(y), width(w), height(h) {}

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

    void set_pos_x(float pos) {
        x = pos;
    }

    void set_pos_y(float pos) {
        y = pos;
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
