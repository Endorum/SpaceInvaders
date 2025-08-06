#pragma once

#include "../model/Constants.hpp"
#include <SFML/Graphics.hpp>

class Player{
public:
    Player(int start_pos=constants::VIEW_WIDTH/2) : position(start_pos), health(3), width(20) {}

    


    void move_left(int amount=1){
        position -= amount;

        if(!in_bounds()){
            position += amount;
        }
    } 

    void move_right(int amount=1){
        position += amount;

        if(!in_bounds()){
            position -= amount;
        }
    }

private:

    // 3 hp at the start, -1 if hit, dead if health <= 0
    int health;

    // in pixels
    int width;

    bool in_bounds(){
        return (
            (position - width/2 >= 0) && /* left side */
            (position + width/2 <= constants::VIEW_WIDTH) /* right side */
        );
    }

    // in the center (+/- width/2 to both sides)
    int position;

};  