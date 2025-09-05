#include "../model/GameState.hpp"
#pragma once
/**
 * Abstract base class for drawing the game state.
 */
class GameDrawer {
public:
    virtual ~GameDrawer() = default;
    virtual void init() = 0;
    virtual void draw(GameState& state) = 0;
};