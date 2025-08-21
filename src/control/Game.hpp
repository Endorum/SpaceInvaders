#ifndef GAME_H
#define GAME_H

#include <SFML/Graphics.hpp>
#include <vector>

#include "../view/Layer.hpp"
#include "Score.hpp"
#include "Player.hpp"
#include "alien.hpp"
#include "bunker.hpp"



// Game class
class Game {

public:
    //initialize the game (window and controls)
    Game();

    void init_sound(const sf::SoundBuffer& sb);

    // start the game
    void start();



private:
    // processes user input, returns true if window has been closed
    bool input();
    void place_aliens(int amount, sf::Texture& texture, int rows = 5, int elms = 10);
    void place_bunkers(int amount,
            const sf::Texture* t_full_health, 
            const sf::Texture* t_small_damage, 
            const sf::Texture* t_large_damage, 
            const sf::Texture* t_destroid);
    void processInput();

    void load_textures();

    // updates all game elements
    void update(float time_passed);

    // draws the scene
    void draw();

    void finish();

    sf::RenderWindow window;

    void show_lasers();
    void show_aliens();
    void show_bunkers();

    void check_alien_hits();

    void move_aliens(float time_passed);

    void check_player_hits();

    void check_bunker_hits();

    bool check_collision(sf::Sprite s1, sf::Sprite s2);

    // view area and layers
    sf::View view;
    Layer game_layer;

    Player* player;

    std::vector<Alien> aliens;

    float alien_speed;
    float acceleration = 0.001; // increase speed by acceleration every step

    bool alien_direction_right = true;

    bool aliens_at_the_bottom = false;

    Score score;

    std::vector<Bunker> bunkers;

    sf::SoundBuffer alien_death_buffer;
    sf::Sound alien_death_sound;


    // increasing level increases the aliens speed
    // when a level is won it gets incremented
    int level = 1;
};

#endif