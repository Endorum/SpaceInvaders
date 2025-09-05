#include "PlayerController.hpp"

PlayerController::PlayerController(Player& player) : model(player) {}

void PlayerController::move_left() {
    model.move_horizontal(-constants::PLAYER_SPEED);
    if (!model.in_bounds()) {
        model.move_horizontal(constants::PLAYER_SPEED);
    }
}

void PlayerController::move_right() {
    model.move_horizontal(constants::PLAYER_SPEED);
    if (!model.in_bounds()) {
        model.move_horizontal(-constants::PLAYER_SPEED);
    }
}

void PlayerController::shoot_laser() {
    model.add_laser(Laser(model.get_pos_x(), model.get_pos_y() - 20));
}

void PlayerController::decrease_health() {
    model.set_health(model.get_health() - 1);
}

void PlayerController::destroy_laser_at(size_t index) {
    model.remove_laser_at(index);
}

void PlayerController::increase_score(int amount) {
    model.set_score(model.get_score() + amount);
}

bool PlayerController::update(float) {
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
