#pragma once

// define some constants to make code more readable
namespace constants {
    constexpr float VIEW_WIDTH = 800.0f;
    constexpr float VIEW_HEIGHT = 800.0f;
    constexpr unsigned int FRAME_RATE = 60;
    constexpr int ALIEN_ROWS = 5;
    constexpr int ALIEN_COLUMNS = 10;
    constexpr float ALIEN_START_X = 0.0f; // starting x position for the first alien
    constexpr float ALIEN_START_Y = -600.0f; // starting y position for the first alien
    constexpr float ALIEN_SPACING_X = 50.0f;
    constexpr float ALIEN_SPACING_Y = 50.0f;
    constexpr float ALIEN_SPEED = 100.0f; // speed of alien movement in pixels per second
    constexpr float ALIEN_SPEED_VERTICAL = 200.0f; 
}