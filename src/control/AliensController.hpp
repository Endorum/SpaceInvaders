#include <vector>
#include "../model/Alien.hpp"
#include "AlienController.hpp"
#include "RandomUtils.hpp"

class AliensController {
public:
    AliensController(std::vector<Alien>& aliens, bool& alien_direction_right, float& alien_speed) : aliens(aliens), alien_direction_right(alien_direction_right), alien_speed(alien_speed) {}
    void update(float time_passed) {
        move_aliens(time_passed);
    }

    
void place_aliens(int amount, int rows = 5, int elms = 10){
    float x_pos = 0;
    float y_pos = 0;

    aliens.clear(); // clear existing aliens
    for(int i = 0; i < amount; i++){
        x_pos = constants::ALIEN_START_X + (i % elms) * constants::ALIEN_SPACING_X; // 1.5f is the space between aliens
        y_pos = constants::ALIEN_START_Y + (i / elms) * constants::ALIEN_SPACING_Y; // 1.5f is the space between aliens
        Alien alien(x_pos, y_pos);
        aliens.push_back(alien);
    }
}

void destroy_laser_at(Alien& alien, size_t index) {
    AlienController alien_controller(alien); // still a lightweight wrapper
    alien_controller.destroy_laser_at(index);
}

private:
    void move_aliens(float time_passed) {
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
        for (Alien& alien : aliens) {
            AlienController(alien).move_vertical(constants::ALIEN_SPACING_Y);
        } 
    }
}
    std::vector<Alien>& aliens;
    bool& alien_direction_right;
    float& alien_speed;
};