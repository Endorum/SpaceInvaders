#include <SFML/Graphics.hpp>
#include "../model/Positionable.hpp"
#include <cstddef>
#include <concepts>
#include <functional>
#include <string>



class GameSprite {
public:
    GameSprite(Positionable& pos, sf::Texture& texture) : sprite(texture), pos(pos) {
        sprite.setPosition({pos.get_pos_x(), pos.get_pos_y()});
        sprite.setScale({2, 2});
        auto sz = texture.getSize();
        sprite.setOrigin({sz.x / 2.f, sz.y / 2.f});

    }

    void draw() {
        sprite.setPosition({pos.get_pos_x(), pos.get_pos_y()});
    }

    sf::Sprite& get_sprite() {
        return sprite;
    };

private:
    sf::Sprite sprite;
    Positionable& pos;

};
