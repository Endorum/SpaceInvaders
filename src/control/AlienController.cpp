#include "AlienController.hpp"

AlienController::AlienController(Alien& alien) : model(alien) {}

void AlienController::shoot_laser() {
    Laser laser(model.get_pos_x(), model.get_pos_y() + model.get_height() / 2.f);
    model.add_laser(laser);
}

void AlienController::destroy_laser_at(size_t index) {
    model.remove_laser_at(index);
}

bool AlienController::move_horizontal(float dx) {
    return model.move_horizontal(dx);
}

bool AlienController::move_vertical(float dy) {
    return model.move_vertical(dy);
}

void AlienController::update(){
    std::vector<Laser>& lasers = model.get_lasers();
    for(auto it = lasers.begin(); it != lasers.end(); ){
        bool destroy = it->move_vertical(constants::ALIEN_LASER_SPEED);
        if(destroy){
            it = lasers.erase(it);
        }else ++it;
    }
}
