#include "Game.hpp"

#include <SFML/Window/Keyboard.hpp>
#include <SFML/Audio/Sound.hpp>
#include <SFML/Audio/SoundBuffer.hpp>
#include <optional>

#include "../model/Constants.hpp"

#include "RandomUtils.hpp"
#include <unistd.h>

#include "../model/Alien.hpp"
#include "../view/SfDrawer.hpp"

Game::Game() : state(), player_controller(state.get_player()), aliens_controller(state.get_aliens(), state.get_alien_direction_right(), state.get_alien_speed()), window(sf::VideoMode({constants::VIEW_WIDTH, constants::VIEW_HEIGHT}), "Space Invaders"), bunkers_controller(state.get_bunkers()), sounds_controller(), drawer(std::make_unique<SfDrawer>(state, window)) {
    window.setFramerateLimit(constants::FRAME_RATE);
    drawer->init();
}

void Game::draw() {
    window.clear();
    drawer->draw(state);
    if(state.get_aliens().empty()) {
        sleep(2);

        state.set_level(state.get_level() + 1);
        start();

    }
    window.display();
}

void Game::start() {
    // The clock is needed to control the speed of movement
    sf::Clock clock;

    // place aliens in the game
    aliens_controller.place_aliens(constants::ALIEN_COLUMNS * constants::ALIEN_ROWS); // 4x10

    // place bunkers in the game
    bunkers_controller.place_bunkers(constants::BUNKER_AMOUNT);

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

// returns true, if the window has been closed
bool Game::input() {
    while (std::optional<sf::Event> event = window.pollEvent()) {
        if (event->is<sf::Event::Closed>()) {
            window.close();
            return true;
        }
        if (const auto* keyPressed = event->getIf<sf::Event::KeyPressed>()) {
            if (keyPressed->code == sf::Keyboard::Key::Right) {
                player_controller.move_right();
            } else if (keyPressed->code == sf::Keyboard::Key::Left) {
                player_controller.move_left();
            } else if (keyPressed->code == sf::Keyboard::Key::Escape) {
                window.close();
                return true;
            } else if (keyPressed->code == sf::Keyboard::Key::Space){
                player_controller.shoot_laser();
                sounds_controller.play_player_shooting_sound();
            }
        }
        return false;
    }
    return false; // Added
}

void Game::update(float time_passed) {

    player_controller.update(time_passed);

    aliens_controller.update(time_passed);

    check_alien_hits();

    check_player_hits();

    check_bunker_hits();

    
}

void Game::check_player_hits() {
    auto& aliens = state.get_aliens();
    for (Alien& alien : aliens) {
        auto& lasers = alien.get_lasers();
        for (size_t i = 0; i < lasers.size(); ) {
            if (check_collision(lasers[i], state.get_player())) {
                player_controller.decrease_health();
                lasers.erase(lasers.begin() + static_cast<long>(i));
                if (state.get_player().get_health() <= 0) {
                    finish();
                    return;
                }
            } else {
                ++i;
            }
        }
    }
}

void Game::check_alien_hits() {
    auto& lasers = state.get_player().get_lasers();
    auto& aliens = state.get_aliens();

    std::vector<int> lasers_to_remove;
    std::vector<int> aliens_to_remove;

    for (int l = 0; l < static_cast<int>(lasers.size()); ++l) {
        const Laser& laser = lasers[l];
        float lx = laser.get_pos_x();
        float ly = laser.get_pos_y();

        for (int a = 0; a < static_cast<int>(aliens.size()); ++a) {
            const Alien& alien = aliens[a];

            float ax = alien.get_pos_x();
            float ay = alien.get_pos_y();
            float half_w = alien.get_width()  / 2.f;
            float half_h = alien.get_height() / 2.f;

            bool hit =
                lx >= (ax - half_w) && lx <= (ax + half_w) &&
                ly >= (ay - half_h) && ly <= (ay + half_h);

            if (hit) {
                lasers_to_remove.push_back(l);
                aliens_to_remove.push_back(a);
                player_controller.increase_score(10);
                sounds_controller.play_alien_death_sound();
                break; // laser consumed
            }
        }
    }

    // Erase aliens
    std::sort(aliens_to_remove.rbegin(), aliens_to_remove.rend());
    aliens_to_remove.erase(std::unique(aliens_to_remove.begin(), aliens_to_remove.end()),
                           aliens_to_remove.end());
    for (int idx : aliens_to_remove) {
        aliens.erase(aliens.begin() + idx);
    }

    // Erase lasers
    std::sort(lasers_to_remove.rbegin(), lasers_to_remove.rend());
    lasers_to_remove.erase(std::unique(lasers_to_remove.begin(), lasers_to_remove.end()),
                           lasers_to_remove.end());
    for (int idx : lasers_to_remove) {
        lasers.erase(lasers.begin() + idx);
    }
}

void Game::check_bunker_hits() {

    // check for hits from the aliens
    auto& aliens = state.get_aliens();
    auto& player = state.get_player();
    auto& bunkers = state.get_bunkers();
    for(Alien& alien : aliens) {
        auto& lasers = alien.get_lasers();
        for (size_t li = 0; li < lasers.size(); ) {
            bool erased = false;
            for(Bunker& bunker : bunkers){
                if(check_collision(lasers[li], bunker)) {
                    bunkers_controller.damage_bunker(bunker);
                    aliens_controller.destroy_laser_at(alien, li);
                    erased = true;
                    break;
                }
            }
            if(!erased) ++li;
        }
    }

    // check from hits from the player
    auto& player_lasers = player.get_lasers();
    for(size_t i = 0; i < player_lasers.size(); ) {
        bool erased = false;
        for(Bunker& bunker : bunkers){
            if(check_collision(player_lasers[i], bunker)) {
                bunkers_controller.damage_bunker(bunker);
                player_lasers.erase(player_lasers.begin() + static_cast<long>(i));
                erased = true;
                break;
            }
        }
        if(!erased) ++i;
    }
}


bool Game::check_collision(Positionable& s1, Positionable& s2) {
    // check if two sprites collide
    float s1_x = s1.get_pos_x();
    float s1_y = s1.get_pos_y();
    float s2_x = s2.get_pos_x();
    float s2_y = s2.get_pos_y();

    if(
        s1_x >= (s2_x - (s2.get_width() / 2.f)) &&
        s1_x <= (s2_x + (s2.get_width() / 2.f)) &&
        s1_y >= (s2_y - (s2.get_height() / 2.f)) && 
        s1_y <= (s2_y + (s2.get_height() / 2.f))
    ) {
        return true;
    }
    return false;

}

void Game::finish() {
    window.close();
}
