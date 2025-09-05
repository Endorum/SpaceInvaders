#pragma once

// define some constants to make code more readable
namespace constants {
    constexpr int VIEW_WIDTH = 600;
    constexpr int VIEW_HEIGHT = 800;
    constexpr unsigned int FRAME_RATE = 60;
    constexpr int ALIEN_ROWS = 4;
    constexpr int ALIEN_COLUMNS = 10;
    constexpr float ALIEN_START_X = 50.0f; // starting x position for the first alien
    constexpr float ALIEN_START_Y = 50.0f; // starting y position for the first alien
    constexpr float ALIEN_SPACING_X = 50.0f;
    constexpr float ALIEN_SPACING_Y = 50.0f;
    constexpr float ALIEN_SPEED = 0.9f; // speed of alien movement in pixels per second
    constexpr float ALIEN_SPEED_VERTICAL = 200.0f;
    constexpr const float GAME_OVER_HEIGHT = 100.0f;
    constexpr const char* LASER_TEXTURE_PATH = "assets/sprites/laser.png";
    constexpr const char* PLAYER_TEXTURE_PATH = "assets/sprites/player.png";
    constexpr const char* ALIEN_TEXTURE_PATH = "assets/sprites/alien.png";
    constexpr const char* BUNKER_FULL_HEALTH_TEXTURE_PATH = "assets/sprites/bunker_full_health.png";
    constexpr const char* BUNKER_SMALL_DAMAGE_TEXTURE_PATH = "assets/sprites/bunker_small_damage.png";
    constexpr const char* BUNKER_LARGE_DAMAGE_TEXTURE_PATH = "assets/sprites/bunker_large_damage.png";
    constexpr const char* BUNKER_DESTROYED_TEXTURE_PATH = "assets/sprites/bunker_destroyed.png";
    constexpr const char* SCORE_FONT_PATH = "assets/fonts/dejavu.ttf";
    constexpr float ALIEN_LASER_SPEED = 5.0f; // speed of alien lasers in pixels per second
    constexpr float PLAYER_SPEED = 10.0f; // speed of player movement in pixels per second
    constexpr float PLAYER_LASER_SPEED = 5.0f;
    constexpr const float BUNKER_HEIGHT = 70.0f;
    constexpr const float BUNKER_WIDTH = 75.0f;
    constexpr int PLAYER_START_HEALTH = 3;
    constexpr float ACCELERATION = 0.001f; // acceleration of alien movement
    constexpr int BUNKER_HEALTH = 10;
    constexpr int BUNKER_AMOUNT = 4;
    constexpr float SOUND_VOLUME = 50.0f;
    constexpr const char* ALIEN_DEATH_SOUND_PATH = "assets/sounds/invaderkilled.wav";
    constexpr const char* PLAYER_SHOOTING_SOUND_PATH = "assets/sounds/shoot.wav";

}