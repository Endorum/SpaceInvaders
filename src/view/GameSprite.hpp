#include <SFML/Graphics.hpp>
#include "../model/Positionable.hpp"
#include <cstddef>
#include <concepts>
#include <functional>
#include <string>

/**
 * Wrapper class for SFML Sprite associated with a Positionable object.
 */
class GameSprite {
public:
    GameSprite(const Positionable& pos, const sf::Texture& texture) : sprite(texture) {
        sprite.setPosition({pos.get_pos_x(), pos.get_pos_y()});
        sprite.setScale({2, 2});
        auto sz = texture.getSize();
        sprite.setOrigin({sz.x / 2.f, sz.y / 2.f});

    }

    sf::Sprite& get_sprite() {
        return sprite;
    };

private:
    sf::Sprite sprite;

};
