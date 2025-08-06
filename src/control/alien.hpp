#pragma once

#include "../model/Constants.hpp"

#include <SFML/Graphics.hpp>

class Alien{

public:
    Alien(int init_pos_x, int init_pos_y) : pos_x(init_pos_x), pos_y(init_pos_x) {}


    bool in_bounds(){
        return (
            (pos_x - size/2 >= 0) && /* left side */
            (pos_x + size/2 <= constants::VIEW_WIDTH) && /* right side */
            (pos_y - size/2 >= 0) && /* top side */
            (pos_y + size/2 <= constants::VIEW_HEIGHT) /* bottom side */
        );
    }

    // amount <= 0 -> to the left, amount >= 0 -> to the right
    void move_vertically(int amount){
        pos_x += amount;

        // set position back if out of bounds
        if(!in_bounds) {
            pos_x -= amount;
        }
    }

    // amount <= 0 -> up, amount >= 0 -> down
    void move_horizontally(int amount){
        pos_y += amount;

        // set position back if out of bounds
        if(!in_bounds){
            pos_y -= amount;
        }
    }


private:
    int pos_x;
    int pos_y;


    // assuming aliens are square and not rectangular
    int size; 

    // aliens only need one hit to die
    bool alive = true;

    // TODO: think about how many points a kill yields
    int yielding_points = 0;



    

}; 