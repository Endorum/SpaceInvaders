#pragma once
#include "Constants.hpp"
/**
 * Abstract base class for positionable objects in the game.
 */
class Positionable {
public:
    virtual ~Positionable() = default;

    virtual float get_pos_x() const = 0;
    virtual float get_pos_y() const = 0;
    virtual float get_width() const = 0;
    virtual float get_height() const = 0;

    /**
     * Move the object horizontally by dx.
     * @return true if the object is out of bounds after the move, false otherwise.
     */
    virtual bool move_horizontal(float dx) {
        set_position(get_pos_x() + dx, get_pos_y());
        return !in_bounds_horizontal();
    }

    /**
     * Move the object vertically by dy.
     * @return true if the object is out of bounds after the move, false otherwise.
     */
    virtual bool move_vertical(float dy) {
        set_position(get_pos_x(), get_pos_y() + dy);
        return !in_bounds_vertical();
    }

    /**
     * Check if the object is within the bounds of the view horizontally.
     * @return true if in bounds, false otherwise.
     */
    bool in_bounds_horizontal(){
        float half_bound_size = get_width() /2;
        return 
            get_pos_x() >= half_bound_size && get_pos_x() < constants::VIEW_WIDTH - half_bound_size;
    }

    /**
     * Check if the object is within the bounds of the view vertically.
     * @return true if in bounds, false otherwise.
     */
    bool in_bounds_vertical(){
        float half_bound_size = get_height() /2;
        return 
            get_pos_y() >= half_bound_size && get_pos_y() < constants::VIEW_HEIGHT - half_bound_size;
    }

    /**
     * Check if the object is within the bounds of the view both horizontally and vertically.
     * @return true if in bounds, false otherwise.
     */
    bool in_bounds(){
        return in_bounds_horizontal() && in_bounds_vertical();
    }

protected:
    virtual void set_position(float x, float y) = 0;
};
