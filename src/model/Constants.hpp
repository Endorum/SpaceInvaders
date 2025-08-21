#pragma once

// define some constants to make code more readable
namespace constants {
    constexpr int VIEW_WIDTH = 600;
    constexpr int VIEW_HEIGHT = 1000;
    constexpr unsigned int FRAME_RATE = 60;
    constexpr int ALIEN_ROWS = 4;
    constexpr int ALIEN_COLUMNS = 10;
    constexpr float ALIEN_START_X = 50.0f; // starting x position for the first alien
    constexpr float ALIEN_START_Y = -(VIEW_HEIGHT - 100); // starting y position for the first alien
    constexpr float ALIEN_SPACING_X = 50.0f;
    constexpr float ALIEN_SPACING_Y = 50.0f;
    constexpr float ALIEN_SPEED = 0.4f; // speed of alien movement in pixels per second
    constexpr float ALIEN_SPEED_VERTICAL = 200.0f;
    constexpr const float GAME_OVER_HEIGHT = 100.0f;
    constexpr const char* LASER_TEXTURE_PATH = "assets/sprites/laser.png";
    constexpr const char* SCORE_FONT_PATH = "assets/fonts/dejavu.ttf";
    constexpr const float BUNKER_HEIGHT = 150.0f;

}