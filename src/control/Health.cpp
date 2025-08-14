#include "Health.hpp"

Health::Health(int initial_health) : health(initial_health) {}

void Health::decrease(int amount) {
    health -= amount;
    if (health < 0) {
        health = 0;
    }
}

int Health::get_health() const {
    return health;
}
