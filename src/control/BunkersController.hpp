#include <vector>
#include "../model/Bunker.hpp"

class BunkersController {
public:
    BunkersController(std::vector<Bunker>& bunkers) : bunkers(bunkers) {}

    void place_bunkers(int amount) {
        float x_pos = 0;
        float y_pos = constants::VIEW_HEIGHT - 150; // fixed y position for all bunkers

        bunkers.clear();
        float spacing = constants::VIEW_WIDTH / (amount + 1);
        for(int i = 0; i < amount; i++){
            x_pos = spacing * (i + 1);
            Bunker bunker(x_pos, y_pos);
            bunkers.push_back(bunker);
        }
    }

    void damage_bunker(Bunker& bunker, int amount = 1) {
        bunker.set_health(bunker.get_health() - amount);
        for(int i = 0; i < bunkers.size(); i++) {
            if(&bunkers[i] == &bunker) {
                if(bunker.get_health() <= 0) {
                    bunkers.erase(bunkers.begin() + i);
                } 
                break;
            }
        }
    }
private:
    std::vector<Bunker>& bunkers;
};