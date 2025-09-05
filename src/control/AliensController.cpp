#include "AliensController.hpp"

AliensController::AliensController(std::vector<Alien>& aliens, bool& alien_direction_right, float& alien_speed)
    : aliens(aliens), alien_direction_right(alien_direction_right), alien_speed(alien_speed) {}

bool AliensController::update(float time_passed) {
    return move_aliens(time_passed);
}

void AliensController::place_aliens(int amount, int rows, int elms) {
    float x_pos = 0;
    float y_pos = 0;

    aliens.clear();
    for(int i = 0; i < amount; i++){
        x_pos = constants::ALIEN_START_X + (i % elms) * constants::ALIEN_SPACING_X;
        y_pos = constants::ALIEN_START_Y + (i / elms) * constants::ALIEN_SPACING_Y;
        Alien alien(x_pos, y_pos);
        aliens.push_back(alien);
    }
}

void AliensController::destroy_laser_at(Alien& alien, size_t index) {
    AlienController alien_controller(alien);
    alien_controller.destroy_laser_at(index);
}

bool AliensController::move_aliens(float time_passed) {
    (void)time_passed; // currently unused
    bool direction_right = alien_direction_right;
    bool direction_changed = false;
    for (Alien& alien : aliens) {
        AlienController alien_controller(alien);
        if (RandomUtils::get_random_int(0, 1000) < 1) {
            alien_controller.shoot_laser();
        }
        alien_controller.update();
        alien_controller.move_horizontal(direction_right ? alien_speed : -alien_speed);
        if (!alien.in_bounds() && !direction_changed) {
            alien_direction_right = !alien_direction_right;
            direction_changed = true;
        }
    }
    if (direction_changed) {
        bool out_of_bounds = true;
        for (Alien& alien : aliens) {
            out_of_bounds = AlienController(alien).move_vertical(constants::ALIEN_SPACING_Y);
        }
        if (out_of_bounds) {
            return true;
        }
    }
    return false;
}
