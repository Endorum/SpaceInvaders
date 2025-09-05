#include <SFML/Audio.hpp>
#include <iostream>
#include "../model/Constants.hpp"

class SoundsController {
public:
    SoundsController() {
        init();
    }
    ~SoundsController() = default;

    void play_alien_death_sound() {
        sf::Sound alien_death_sound = sf::Sound(alien_death_buffer);
        alien_death_sound.setVolume(constants::SOUND_VOLUME);
        alien_death_sound.play();
    }

    void play_player_shooting_sound() {
        sf::Sound player_shooting_sound = sf::Sound(player_shooting_buffer);
        player_shooting_sound.setVolume(constants::SOUND_VOLUME);
        player_shooting_sound.play();
    }

private:
    sf::SoundBuffer alien_death_buffer;
    sf::SoundBuffer player_shooting_buffer;
    
    void init() {
        
        if(!alien_death_buffer.loadFromFile(constants::ALIEN_DEATH_SOUND_PATH)){
            std::cerr << "Could not load sound for invader kill" << std::endl;
            exit(1);
        }
        sf::SoundBuffer player_shooting_buffer;
        if(!player_shooting_buffer.loadFromFile(constants::PLAYER_SHOOTING_SOUND_PATH)){
            std::cerr << "Could not load sound for player shooting" << std::endl;
            exit(1);
        }
    }
};

