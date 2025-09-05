#include <SFML/Graphics.hpp>
#include "Layer.hpp"
#include "../model/Constants.hpp"
#include "GameDrawer.hpp"
#include "GameSprite.hpp"
#include "TextFactory.hpp"

class SfDrawer : public GameDrawer {
public:
    SfDrawer(GameState& game_state, sf::RenderWindow& window)
      : game_layer(window), view(window.getDefaultView()), state(game_state) {}
    ~SfDrawer() override = default;

void init() override {


    // set the view (visible area) for our game
    game_layer.set_view(view);

    // load textures
    alien_texture = load_texture(constants::ALIEN_TEXTURE_PATH);
    player_texture = load_texture(constants::PLAYER_TEXTURE_PATH);
    laser_texture = load_texture(constants::LASER_TEXTURE_PATH);
    bunker_full_health_texture = load_texture(constants::BUNKER_FULL_HEALTH_TEXTURE_PATH);
    bunker_small_damage_texture = load_texture(constants::BUNKER_SMALL_DAMAGE_TEXTURE_PATH);
    bunker_large_damage_texture = load_texture(constants::BUNKER_LARGE_DAMAGE_TEXTURE_PATH);
    bunker_destroyed_texture = load_texture(constants::BUNKER_DESTROYED_TEXTURE_PATH);
    }

void draw(GameState& state) override {
    game_layer.clear();

    show_player();

    show_text();

    show_aliens();
    show_lasers();
    show_bunkers();
    
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

void show_win_message() {
    sf::Text win_text = TextFactory::create_score_text("You Win!", 50, constants::VIEW_WIDTH / 2.f - 100, constants::VIEW_HEIGHT / 2.f - 25);
    game_layer.add_to_layer(win_text);
}

void show_bunkers() {
    for(size_t i=0;i<state.get_bunkers().size(); i++){
        Bunker& bunker = state.get_bunkers().at(i);

        if(bunker.get_health() <= 0){
            continue;
        }

        const sf::Texture* tex = &bunker_full_health_texture;
        

        int health = bunker.get_health();

        if(health >= 9){
            tex = &bunker_full_health_texture;
        } else if(health >= 6){
            tex = &bunker_small_damage_texture;
        } else if(health >= 3){
            tex = &bunker_large_damage_texture;
        } else {
            tex = &bunker_destroyed_texture;
        }

        GameSprite bunker_sprite(bunker, *tex);
        game_layer.add_to_layer(bunker_sprite.get_sprite());
    }
}

void show_text() {
    sf::Text score = TextFactory::create_score_text("Score: " + std::to_string(state.get_player().get_score()), 20, 20, 0);
    sf::Text health = TextFactory::create_score_text("Health: " + std::to_string(state.get_player().get_health()), 20, 20, 30);
    sf::Text level = TextFactory::create_score_text("Level: " + std::to_string(state.get_level()), 20, 20, 60);
    game_layer.add_to_layer(score);
    game_layer.add_to_layer(health);
    game_layer.add_to_layer(level);
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
        std::vector<Laser>& alien_lasers = alien.get_lasers();
        for(int i=0;i<alien_lasers.size();i++){
            GameSprite laser_sprite = GameSprite(alien_lasers.at(i), laser_texture);
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

    sf::Texture bunker_full_health_texture;
    sf::Texture bunker_small_damage_texture;
    sf::Texture bunker_large_damage_texture;
    sf::Texture bunker_destroyed_texture;
};