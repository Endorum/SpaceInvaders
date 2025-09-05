#include "control/Game.hpp"

template<typename T>
concept Hashable = requires(T a)
{
    { std::hash<T>{}(a) } -> std::convertible_to<std::size_t>;
};

int main() {
    Game game;

    game.start();

    ;
}