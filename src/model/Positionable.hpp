#pragma once
#include "Constants.hpp"
class Positionable {
public:
    virtual ~Positionable() = default;

    virtual float get_pos_x() const = 0;
    virtual float get_pos_y() const = 0;
    virtual float get_width() const = 0;
    virtual float get_height() const = 0;

    virtual bool move_horizontal(float dx) {
        set_position(get_pos_x() + dx, get_pos_y());
        return !in_bounds();
    }

    virtual bool move_vertical(float dy) {
        set_position(get_pos_x(), get_pos_y() + dy);
        return !in_bounds();
    }

    bool in_bounds(){
        float half_bound_size = get_width() /2;
        return 
            get_pos_x() >= half_bound_size && get_pos_x() < constants::VIEW_WIDTH - half_bound_size;
    }

protected:
    virtual void set_position(float x, float y) = 0;
};
