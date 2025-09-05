#include "BunkersController.hpp"

BunkersController::BunkersController(std::vector<Bunker>& bunkers) : bunkers(bunkers) {}

void BunkersController::place_bunkers(int amount) {
    float x_pos = 0;
    float y_pos = constants::VIEW_HEIGHT - 150; // fixed y position

    bunkers.clear();
    float spacing = constants::VIEW_WIDTH / (amount + 1);
    for(int i = 0; i < amount; i++){
        x_pos = spacing * (i + 1);
        Bunker bunker(x_pos, y_pos);
        bunkers.push_back(bunker);
    }
}

void BunkersController::damage_bunker(size_t index, int amount) {
    if(index >= bunkers.size()) return;

    Bunker& bunker = bunkers[index];
    bunker.set_health(bunker.get_health() - amount);

    if(bunker.get_health() <= 0){
        bunkers.erase(bunkers.begin() + static_cast<long>(index));
    }
}
