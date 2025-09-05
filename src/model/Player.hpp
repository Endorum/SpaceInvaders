#pragma once
#include <vector>
#include <algorithm>
#include "Positionable.hpp"
#include "Laser.hpp"

class Player : public Positionable {
public:
    Player(float x, float y)
        : x(x), y(y), width(50), height(50), score(0), health(3) {}

    // Positionable interface
    float get_pos_x() const override { return x; }
    float get_pos_y() const override { return y; }
    float get_width()  const override { return width; }
    float get_height() const override { return height; }

    int  get_score()  const { return score; }
    int  get_health() const { return health; }
    void set_score(int s)   { score = s; }
    void set_health(int h)  { health = h; }

    void add_laser(const Laser laser) {
        lasers.push_back(laser);
    }

    std::vector<Laser>& get_lasers() { return lasers; }
    const std::vector<Laser>& get_lasers() const { return lasers; }

    /**
     * Remove laser at the specified index in the laser list.
     */
    void remove_laser_at(size_t index) {
        if (index < lasers.size()) {
            lasers.erase(lasers.begin() + static_cast<long>(index));
        }
    }

private:
    // coordinates
    float x, y;
    // dimensions
    float width, height;
    // player score (aliens destroyed * 10)
    int score;
    // player health (number of hits the player can take)
    int health;
    // player's lasers
    std::vector<Laser> lasers;

    void set_position(float nx, float ny) override {
        x = nx;
        y = ny;
    }
};
