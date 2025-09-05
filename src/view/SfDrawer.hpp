#include <SFML/Graphics.hpp>
#include "Layer.hpp"
#include "../model/Constants.hpp"
#include "GameDrawer.hpp"
#include "GameSprite.hpp"
#include "TextFactory.hpp"

class SfDrawer : public GameDrawer {
public:
    SfDrawer(GameState& game_state, sf::RenderWindow& window)
      : game_layer(window), state(game_state), view(window.getDefaultView()) {}
    ~SfDrawer() override = default;

void init() override {


    // set the view (visible area) for our game
    game_layer.set_view(view);

    alien_texture = load_texture(constants::ALIEN_TEXTURE_PATH);
    player_texture = load_texture(constants::PLAYER_TEXTURE_PATH);
    laser_texture = load_texture(constants::LASER_TEXTURE_PATH);
    }

void draw(GameState& state) override {
    game_layer.clear();

    show_player();

    show_text();

    show_aliens();
    show_lasers();
    
    game_layer.draw();
}

private:

sf::Texture load_texture(const std::string& texture_file) {
        sf::Texture tex;
        bool loaded = false;
        if (!loaded) {
            if (!tex.loadFromFile(texture_file)) {
                throw std::runtime_error("Failed to load texture: " + texture_file);
            }
            loaded = true;
        }
        return tex;
    }

void show_text() {
    sf::Text score = TextFactory::create_score_text("Score: " + std::to_string(state.get_player().get_score()), 20, 20, 0);
    sf::Text health = TextFactory::create_score_text("Health: " + std::to_string(state.get_player().get_health()), 20, 20, 30);
    game_layer.add_to_layer(score);
    game_layer.add_to_layer(health);
}

void show_player() {
    GameSprite player_sprite = GameSprite(state.get_player(), player_texture);
    game_layer.add_to_layer(player_sprite.get_sprite());
}

void show_aliens() {
    for(int i=0;i<state.get_aliens().size();i++){
        GameSprite alien_sprite = GameSprite(state.get_aliens().at(i), alien_texture);
        game_layer.add_to_layer(alien_sprite.get_sprite());
    }
}

void show_lasers() {
    auto& lasers = state.get_player().get_lasers();
    for(int i=0;i<lasers.size();i++){
        GameSprite laser_sprite = GameSprite(lasers.at(i), laser_texture);
        game_layer.add_to_layer(laser_sprite.get_sprite());
    }
    std::vector<Alien>& aliens = state.get_aliens();
    for(Alien& alien : aliens) {
        std::vector<Laser*>& alien_lasers = alien.get_lasers();
        for(int i=0;i<alien_lasers.size();i++){
            GameSprite laser_sprite = GameSprite(*alien_lasers.at(i), laser_texture);
            game_layer.add_to_layer(laser_sprite.get_sprite());
        }
    }
}
    Layer game_layer;
    sf::View view;
    GameState& state;

    sf::Texture player_texture;
    sf::Texture alien_texture;
    sf::Texture laser_texture;
};