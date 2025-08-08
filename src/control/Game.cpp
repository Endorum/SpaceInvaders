#include "Game.hpp"

#include <SFML/Window/Keyboard.hpp>
#include <optional>

#include "../model/Constants.hpp"

Game::Game() : window(sf::VideoMode({constants::VIEW_WIDTH, constants::VIEW_HEIGHT}), "Space Invaders"),
    view(sf::FloatRect(sf::Vector2f({0,-constants::VIEW_HEIGHT}), sf::Vector2f({constants::VIEW_WIDTH,constants::VIEW_HEIGHT}))),
    game_layer(window) {
    // limit frame rate
    window.setFramerateLimit(constants::FRAME_RATE);

    // set the view (visible area) for our game
    game_layer.set_view(view);
}

// 5 rows x 10 elms 
void Game::place_aliens(int amount, sf::Texture& texture, int rows, int elms){
    float x_pos = 0;
    float y_pos = 0;

    aliens.clear();
    for(int i = 0; i < amount; i++){
        x_pos = constants::ALIEN_START_X + (i % elms) * constants::ALIEN_SPACING_X; // 1.5f is the space between aliens
        y_pos = constants::ALIEN_START_Y + (i / elms) * constants::ALIEN_SPACING_Y; // 1.5f is the space between aliens
        Alien alien(x_pos, y_pos, texture);
        aliens.push_back(alien);
    }
}

void Game::show_lasers(){
    std::vector<Laser*> lasers = player->get_lasers();
    for(int i=0;i<lasers.size();i++){
        game_layer.add_to_layer(lasers.at(i)->get_sprite());
    }
}

void Game::start() {
    // The clock is needed to control the speed of movement
    sf::Clock clock;

    sf::Texture player_texture;

    // load player texture 
    if(!player_texture.loadFromFile("assets/sprites/player.png")){
        std::cerr << "Could not load player texture" << std::endl;
        exit(1);
    }

    sf::Texture laser_texture;
    // load laser texture 
    if(!laser_texture.loadFromFile("assets/sprites/laser.png")){
        std::cerr << "Could not load laser texture" << std::endl;
        exit(1);
    }

    // create player
    player = new Player(player_texture, laser_texture);

    sf::Texture alien_texture;
    // load alien texture
    if(!alien_texture.loadFromFile("assets/sprites/alien.png")){
        std::cerr << "Could not load alien texture" << std::endl;
        exit(1);
    }

    // place aliens in the game
    place_aliens(40, alien_texture);

    while (window.isOpen()) {
        // Restart the clock and save the elapsed time into elapsed_time
        sf::Time elapsed_time = clock.restart();

        
 
        // handle input, check if window is still open
        if (!input()) {
            // update the scene according to the passed time
            update(elapsed_time.asSeconds());
            // draw the scene
            draw();
        }
    }
}

void Game::processInput(){
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Right)){
        player->move_right();
    }

    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Left)){
        player->move_left();
    }
}

// returns true, if the window has been closed
bool Game::input() {
    while (std::optional<sf::Event> event = window.pollEvent()) {
        if (event->is<sf::Event::Closed>()) {
            // quit
            window.close();
            return true;
        }
        if (const auto* keyPressed = event->getIf<sf::Event::KeyPressed>()) {
            if (keyPressed->code == sf::Keyboard::Key::Right) {
                player->move_right();
            } else if (keyPressed->code == sf::Keyboard::Key::Left) {
                player->move_left();
            } else if (keyPressed->code == sf::Keyboard::Key::Escape) {
                window.close();
                return true;
            } else if (keyPressed->code == sf::Keyboard::Key::Space){ // Space to shoot
                player->shoot_laser();
            }
    }
    return false;
}
}

void Game::update(float time_passed) {
    // TODO: update the game objects with the current time stamp
    //processInput();

    player->update();
}

void Game::add_aliens_to_layer() {
    for(int i=0;i<aliens.size();i++){
        game_layer.add_to_layer(aliens.at(i).get_sprite());
    }
}

void Game::draw() {
    window.clear();

    game_layer.clear();
    

    // add player sprite to layer
    game_layer.add_to_layer(player->get_sprite());

    // add alien sprites to layer
    add_aliens_to_layer();
    
    // show the lasers
    show_lasers();

    game_layer.draw();

    window.display();
}
