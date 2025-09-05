#pragma once

// define some constants to make code more readable
namespace constants {
    constexpr int VIEW_WIDTH = 1000;
    constexpr int VIEW_HEIGHT = 1000;
    constexpr unsigned int FRAME_RATE = 60;
    constexpr int ALIEN_ROWS = 4;
    constexpr int ALIEN_COLUMNS = 10;
    constexpr float ALIEN_START_X = 50.0f; // starting x position for the first alien
    constexpr float ALIEN_START_Y = 50.0f; // starting y position for the first alien
    constexpr float ALIEN_SPACING_X = 50.0f;
    constexpr float ALIEN_SPACING_Y = 50.0f;
    constexpr float ALIEN_SPEED = 1.0f; // speed of alien movement in pixels per second
    constexpr float ALIEN_SPEED_VERTICAL = 200.0f;
    constexpr const char* LASER_TEXTURE_PATH = "assets/sprites/laser.png";
    constexpr const char* PLAYER_TEXTURE_PATH = "assets/sprites/player.png";
    constexpr const char* ALIEN_TEXTURE_PATH = "assets/sprites/alien.png";
    constexpr const char* SCORE_FONT_PATH = "assets/fonts/dejavu.ttf";
    constexpr float ALIEN_LASER_SPEED = 5.0f; // speed of alien lasers in pixels per second
    constexpr float PLAYER_SPEED = 10.0f; // speed of player movement in pixels per second
    constexpr float PLAYER_LASER_SPEED = 5.0f;
}