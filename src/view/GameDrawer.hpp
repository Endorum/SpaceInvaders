#include "../model/GameState.hpp"
#pragma once
class GameDrawer {
public:
    virtual ~GameDrawer() = default;
    virtual void init() = 0;
    virtual void draw(GameState& state) = 0;
};