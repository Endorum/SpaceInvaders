#include <SFML/Audio.hpp>
#include <iostream>
#include "../model/Constants.hpp"

class SoundsController {
public:
    SoundsController() : alien_death_sound(alien_death_buffer), player_shooting_sound(player_shooting_buffer) {
        init();
    }
    ~SoundsController() = default;

    void play_alien_death_sound() {
        alien_death_sound = sf::Sound(alien_death_buffer);
        alien_death_sound.setVolume(constants::SOUND_VOLUME);
        alien_death_sound.play();
    }

    void play_player_shooting_sound() {
        player_shooting_sound = sf::Sound(player_shooting_buffer);
        player_shooting_sound.setVolume(constants::SOUND_VOLUME);
        player_shooting_sound.play();
    }

private:
    sf::SoundBuffer alien_death_buffer;
    sf::SoundBuffer player_shooting_buffer;

    sf::Sound alien_death_sound;
    sf::Sound player_shooting_sound;

    void init() {
        
        if(!alien_death_buffer.loadFromFile(constants::ALIEN_DEATH_SOUND_PATH)){
            std::cerr << "Could not load sound for invader kill" << std::endl;
            exit(1);
        }
        
        if(!player_shooting_buffer.loadFromFile(constants::PLAYER_SHOOTING_SOUND_PATH)){
            std::cerr << "Could not load sound for player shooting" << std::endl;
            exit(1);
        }
    }
};

