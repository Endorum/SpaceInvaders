#pragma once

#include <SFML/Audio.hpp>
#include <iostream>
#include "../model/Constants.hpp"

/**
 * Controller for managing game sounds.
 */
class SoundsController {
public:
    SoundsController();
    ~SoundsController() = default;

    /**
     * Play the sound for alien death.
     */
    void play_alien_death_sound();

    /**
     * Play the sound for player shooting.
     */
    void play_player_shooting_sound();
private:
    sf::SoundBuffer alien_death_buffer;
    sf::SoundBuffer player_shooting_buffer;
    sf::Sound alien_death_sound;
    sf::Sound player_shooting_sound;
    void init();
};

