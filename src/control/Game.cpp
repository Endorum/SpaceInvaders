#include "Game.hpp"

#include <SFML/Window/Keyboard.hpp>
#include <optional>

#include "../model/Constants.hpp"
#include "Score.hpp"

#include "TextFactory.hpp"

#include "RandomUtils.hpp"
#include <unistd.h>

Game::Game() : window(sf::VideoMode({constants::VIEW_WIDTH, constants::VIEW_HEIGHT}), "Space Invaders"),
    view(sf::FloatRect(sf::Vector2f({0,-constants::VIEW_HEIGHT}), sf::Vector2f({constants::VIEW_WIDTH,constants::VIEW_HEIGHT}))),
    game_layer(window), score(0) {

    
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

void Game::place_bunkers(int amount,
    const sf::Texture* t_full_health, 
    const sf::Texture* t_small_damage, 
    const sf::Texture* t_large_damage, 
    const sf::Texture* t_destroid)   {

    float pos_x = 0;
    float pos_y = -constants::BUNKER_HEIGHT;

    for(int i=0;i<amount;i++){
        // spacing factor
        float segment = constants::VIEW_WIDTH / (amount + 1);

        // position: center each bunker in its segment
        pos_x = (i + 1) * segment;

        // create Bunker
        Bunker bunker(pos_x, pos_y, t_full_health, t_small_damage, t_large_damage, t_destroid);

        bunkers.push_back(bunker);
    }

}

void Game::show_lasers(){
    std::vector<Laser*> lasers = player->get_lasers();
    for(int i=0;i<lasers.size();i++){
        game_layer.add_to_layer(lasers.at(i)->get_sprite());
    }
    for(Alien& alien : aliens) {
        std::vector<Laser*>& alien_lasers = alien.get_lasers();
        for(int i=0;i<alien_lasers.size();i++){
            game_layer.add_to_layer(alien_lasers.at(i)->get_sprite());
        }
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

    // create player
    player = new Player(player_texture);

    sf::Texture alien_texture;
    // load alien texture
    if(!alien_texture.loadFromFile("assets/sprites/alien.png")){
        std::cerr << "Could not load alien texture" << std::endl;
        exit(1);
    }

    // place aliens in the game
    place_aliens(constants::ALIEN_COLUMNS * constants::ALIEN_ROWS, alien_texture); // 4x10

    sf::Texture t_full_health;
    sf::Texture t_small_damage;
    sf::Texture t_large_damage;
    sf::Texture t_destroid;

    // load bunker textures
    if(!t_full_health.loadFromFile("assets/sprites/Bunker.png")){
        std::cerr << "Could not load full health bunker texture" << std::endl;
        exit(1);
    }
    if(!t_small_damage.loadFromFile("assets/sprites/BunkerLittleDamage.png")){
        std::cerr << "Could not load small damage bunker texture" << std::endl;
        exit(1);
    }
    if(!t_large_damage.loadFromFile("assets/sprites/BunkerMoreDamage.png")){
        std::cerr << "Could not load large damage bunker texture" << std::endl;
        exit(1);
    }
    if(!t_destroid.loadFromFile("assets/sprites/BunkerDestroid.png")){
        std::cerr << "Could not load destroid bunker texture" << std::endl;
        exit(1);
    }

    place_bunkers(4, &t_full_health, &t_small_damage, &t_large_damage, &t_destroid);


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

    return false;
}

void Game::update(float time_passed) {
    // TODO: update the game objects with the current time stamp

    player->update();

    check_alien_hits();

    check_player_hits();

    check_bunker_hits();

    // change the sprite accordingly, and remove the bunker if its health is <= 0
    for (auto it = bunkers.begin(); it != bunkers.end(); ) {
        if (it->update()) {
            it = bunkers.erase(it); // erase returns the next iterator
        } else {
            ++it;
        }
    }
        

    move_aliens(time_passed);

    processInput();


    

}

void Game::show_aliens() {
    for(int i=0;i<aliens.size();i++){
        game_layer.add_to_layer(aliens.at(i).get_sprite());
    }
}

void Game::show_bunkers() {
    for(int i=0;i<bunkers.size();i++){
        game_layer.add_to_layer(bunkers.at(i).get_sprite());
    }
}

bool Game::check_collision(sf::Sprite s1, sf::Sprite s2) {
    // check if two sprites collide
    float s1_x = s1.getPosition().x;
    float s1_y = s1.getPosition().y;
    float s2_x = s2.getPosition().x;
    float s2_y = s2.getPosition().y;

    if(
        s1_x >= (s2_x - (s2.getGlobalBounds().size.x / 2.f)) &&
        s1_x <= (s2_x + (s2.getGlobalBounds().size.x / 2.f)) &&
        s1_y >= (s2_y - (s2.getGlobalBounds().size.y / 2.f)) && 
        s1_y <= (s2_y + (s2.getGlobalBounds().size.y / 2.f))
    ) {
        return true;
    }
    return false;

}

void Game::check_player_hits() {
    for(Alien& alien : aliens) {
        for(Laser* laser : alien.get_lasers()) {
            if(check_collision(laser->get_sprite(), player->get_sprite())) {
                player->decrease_health();
                alien.destroy_laser(laser);
                if(player->get_health() <= 0) {
                    finish(); // end the game if player health is 0
                }
            }
        }
    }
}

void Game::check_bunker_hits() {

    // check for hits from the aliens
    for(Alien& alien : aliens) {
        for(Laser* laser : alien.get_lasers()) {
            for(Bunker& bunker : bunkers){
                if(check_collision(laser->get_sprite(), bunker.get_sprite())) {
                    bunker.damage();
                    alien.destroy_laser(laser);
                }
            }
        }
    }

    // check from hits from the player
    for(Laser* laser : player->get_lasers()){
        for(Bunker& bunker : bunkers){
            if(check_collision(laser->get_sprite(), bunker.get_sprite())) {
                bunker.damage();
                player->destroy_laser(laser);
            }
        }
    }
}

void Game::check_alien_hits() {
    // check for player_laser -> alien hit
    std::vector<int> lasers_to_remove;
    std::vector<Alien*> aliens_to_remove;

    
    std::vector<Laser*>& lasers = player->get_lasers();
    for (int laser_idx = 0; laser_idx < lasers.size(); laser_idx++) {
        Laser* laser = lasers[laser_idx];

        for (int alien_idx = 0; alien_idx < aliens.size(); alien_idx++) {
            Alien& alien = aliens[alien_idx];



            float laser_x = laser->get_pos_x();
            float laser_y = laser->get_pos_y();

            float alien_x = alien.get_pos_x();
            float alien_y = alien.get_pos_y();
            

            // assuming the lasers have no width or height, can be changed later
            if(
                laser_x >= (alien_x - (alien.get_bound_size_x() / 2.f)) &&
                laser_x <= (alien_x + (alien.get_bound_size_x() / 2.f)) &&
                laser_y >= (alien_y - (alien.get_bound_size_y() / 2.f)) && 
                laser_y <= (alien_y + (alien.get_bound_size_y() / 2.f))
            ){
                lasers_to_remove.push_back(laser_idx);
                aliens_to_remove.push_back(&alien);
                score.increase(10); // increase score by 10 for each alien hit
                break; // One laser can only hit one alien
            }
        }
    }

    // Remove hit aliens
    for(Alien* alien_ptr : aliens_to_remove){
        for(auto it = aliens.begin(); it != aliens.end(); it++){
            if(&(*it) == alien_ptr){
                aliens.erase(it);
                break;
            }
        }
    }

    // Remove lasers
    std::sort(lasers_to_remove.rbegin(), lasers_to_remove.rend());
    for (int idx : lasers_to_remove) {
        delete lasers[idx];
        lasers.erase(lasers.begin() + idx);
    }
}

void Game::move_aliens(float time_passed) {
    
    bool direction_right = alien_direction_right;
    bool direction_changed = false;

    // increase speed over time
    alien_speed += acceleration;

    for(Alien& alien : aliens) {

        if(RandomUtils::get_random_int(0, 1000) < 1) { // 0.1% chance to shoot
            alien.shoot_laser();
        }
        alien.update();

        
        
        if(direction_right) {
            alien.move_horizontally(alien_speed);
        } else {
            alien.move_horizontally(-alien_speed);
        }
        if(!alien.in_bounds() && !direction_changed) {
            alien_direction_right = !alien_direction_right;
            direction_changed = true;
        }
        if(!alien.in_bounds_vertical()) {
            finish();
            return; // end the game if any alien has reached the bottom of the screen
        }
    }
    
    if(direction_changed) {
        for(Alien& alien : aliens) {
            alien.move_vertically(constants::ALIEN_SPACING_Y);
        }
    }


    
}

void Game::draw() {
    window.clear();

    game_layer.clear();
    
    
    // add player sprite to layer
    game_layer.add_to_layer(player->get_sprite());

    game_layer.add_to_layer(score.get_text());

    sf::Text health = TextFactory::create_score_text("Health: " + std::to_string(player->get_health()), 20, 10, -constants::VIEW_HEIGHT + 50);

    game_layer.add_to_layer(health);

    // show the aliens
    show_aliens(); 
    
    // show the lasers
    show_lasers();

    // show the bunkers
    show_bunkers();

        

    // exit(0);

    // win if all aliens are dead
    if(aliens.empty()){
        // show "You Win" and wait for a few seconds?
        sf::Text win_msg = TextFactory::create_score_text("You Win!", 20, (constants::VIEW_WIDTH / 2.f) - 50, -constants::VIEW_HEIGHT / 2.f);
        game_layer.add_to_layer(win_msg);
        // finish();
    }
    
    game_layer.draw();
    
    window.display();

    if(aliens.empty()) {
        sleep(2);
        finish();
    }
}

void Game::finish() {
    window.close();
}
