#pragma once

#include "../model/Constants.hpp"

#include <SFML/Graphics.hpp>
#include "../model/Alien.hpp"

class AlienController{

public:
    AlienController(Alien& alien) : model(alien){}

    void shoot_laser() {
        Laser* laser = new Laser(model.get_pos_x(), model.get_pos_y() + model.get_height() / 2.f);
        model.add_laser(laser);
    }

    void destroy_laser(Laser* laser) {
        std::vector<Laser*>& lasers = model.get_lasers();
        auto it = std::find(lasers.begin(), lasers.end(), laser);
        if (it != lasers.end()) {
            delete *it; // delete the laser object
            lasers.erase(it); // remove from the vector
        }
    }

    bool move_horizontal(float dx) {
        return model.move_horizontal(dx);
    }

    bool move_vertical(float dy) {
        return model.move_vertical(dy);
    }

    void update(){
        // move the aliens lasers down
        std::vector<Laser*>& lasers = model.get_lasers();
        for(auto it = lasers.begin(); it != lasers.end(); ){
            Laser* laser = *it;
            bool destroy = laser->move_vertical(constants::ALIEN_LASER_SPEED);
            if(destroy){
                delete laser;
                it = lasers.erase(it);
            }else it++;
        }
    }



private:
    Alien& model;

};