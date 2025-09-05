#include "../model/Constants.hpp"
#include "../model/Player.hpp"
#include "../model/Laser.hpp"

class PlayerController {
public:
    PlayerController(Player& player) : model(player) {}

    void move_left() {
        model.move_horizontal(-constants::PLAYER_SPEED);
        if (!model.in_bounds()) {
            model.move_horizontal(constants::PLAYER_SPEED);
        }
    }

    void move_right() {
        model.move_horizontal(constants::PLAYER_SPEED);
        if (!model.in_bounds()) {
            model.move_horizontal(-constants::PLAYER_SPEED);
        }
    }

    void shoot_laser() {
        model.add_laser(Laser(model.get_pos_x(),
                              model.get_pos_y()-20));
    }

    void decrease_health() {
        model.set_health(model.get_health() - 1);
    }

    void increase_score(int amount) {
        model.set_score(model.get_score() + amount);
    }

    bool update(float /*time_passed*/) {
        bool removed = false;
        auto& lasers = model.get_lasers();
        for (auto it = lasers.begin(); it != lasers.end(); ) {
            bool destroy = it->move_vertical(-constants::PLAYER_LASER_SPEED);
            if (destroy) {
                it = lasers.erase(it);
                removed = true;
            } else {
                ++it;
            }
        }
        return removed;
    }

private:
    Player& model;
};