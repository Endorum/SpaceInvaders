#include "SoundsController.hpp"

SoundsController::SoundsController() : alien_death_sound(alien_death_buffer), player_shooting_sound(player_shooting_buffer) {
    init();
}

void SoundsController::play_alien_death_sound() {
    alien_death_sound = sf::Sound(alien_death_buffer);
    alien_death_sound.setVolume(constants::SOUND_VOLUME);
    alien_death_sound.play();
}

void SoundsController::play_player_shooting_sound() {
    player_shooting_sound = sf::Sound(player_shooting_buffer);
    player_shooting_sound.setVolume(constants::SOUND_VOLUME);
    player_shooting_sound.play();
}

void SoundsController::init() {
    if(!alien_death_buffer.loadFromFile(constants::ALIEN_DEATH_SOUND_PATH)){
        std::cerr << "Could not load sound for invader kill" << std::endl;
        exit(1);
    }

    if(!player_shooting_buffer.loadFromFile(constants::PLAYER_SHOOTING_SOUND_PATH)){
        std::cerr << "Could not load sound for player shooting" << std::endl;
        exit(1);
    }
}
