#include <SFML/Graphics.hpp>
#include <vector>
#include "Positionable.hpp"
#include "Laser.hpp"
#pragma once

class Alien : public Positionable {
public:
    Alien(float x, float y) : x(x), y(y), width(50), height(50) {}

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

    std::vector<Laser>& get_lasers() {
        return lasers;
    }

    /**
     * Add a laser to the alien's laser list.
     */
    void add_laser(Laser laser) {
        lasers.push_back(laser);
    }

    /**
     * Remove laser at the specified index.
     */
    void remove_laser_at(size_t index) {
        if (index < lasers.size()) {
            lasers.erase(lasers.begin() + static_cast<long>(index));
        }
    }


private:
    // alien's lasers
    std::vector<Laser> lasers;
    // coordinates
    float x, y;
    // dimensions
    float width, height;

        void set_position(float x, float y) override {
        this->x = x;
        this->y = y;
    }
};
