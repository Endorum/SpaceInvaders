#pragma once

#include <SFML/Graphics.hpp>
#include "Layer.hpp"
#include "../model/Constants.hpp"
#include "GameDrawer.hpp"
#include "GameSprite.hpp"
#include "TextFactory.hpp"

class SfDrawer : public GameDrawer {
public:
    SfDrawer(GameState& game_state, sf::RenderWindow& window);
    ~SfDrawer() override = default;


    /**
     * Initialize the drawer, load textures and set up the view.
     */
    void init() override;


    /**
     * Draw the game elements on the window.
     */
    void draw(GameState& state) override;

private:

    /**
     * Load a texture from a file.
     * @param texture_file The path to the texture file.
     * @return The loaded sf::Texture object.
     */
    sf::Texture load_texture(const std::string& texture_file);

    // show elements on the screen
    void show_win_message();

    void show_bunkers();

    void show_text();

    void show_player();

    void show_aliens();

    void show_lasers();

    // layer to draw game elements
    Layer game_layer;

    // view for the game
    sf::View view;

    // reference to the game state
    GameState& state;

    // textures
    sf::Texture player_texture;
    sf::Texture alien_texture;
    sf::Texture laser_texture;
    sf::Texture bunker_full_health_texture;
    sf::Texture bunker_small_damage_texture;
    sf::Texture bunker_large_damage_texture;
    sf::Texture bunker_destroyed_texture;
};