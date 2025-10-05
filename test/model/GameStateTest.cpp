#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "../../src/model/GameState.hpp"
#include "../../src/model/Alien.hpp"

TEST(GameStateTest, AddAlien) {
    GameState gameState;
    Alien alien1 = Alien(100.0f, 100.0f);
    Alien alien2 = Alien(150.0f, 100.0f);
    Alien alien3 = Alien(200.0f, 100.0f);

    //add_alien 1
    gameState.add_alien(alien1);
    EXPECT_EQ(gameState.get_aliens().size(), 1);
    EXPECT_EQ(gameState.get_aliens()[0].get_pos_x(), 100.0f);

    //add_alien 2
    gameState.add_alien(alien2);
    EXPECT_EQ(gameState.get_aliens().size(), 2);
    EXPECT_EQ(gameState.get_aliens()[1].get_pos_x(), 150.0f);

    //add_alien 3
    gameState.add_alien(alien3);
    EXPECT_EQ(gameState.get_aliens().size(), 3);
    EXPECT_EQ(gameState.get_aliens()[2].get_pos_x(), 200.0f);
}

TEST(GameStateTest, SetAlienDirectionRight) {
    GameState gameState;

    //set_alien_direction_right 1 - set to true
    gameState.set_alien_direction_right(true);
    EXPECT_EQ(gameState.get_alien_direction_right(), true);

    //set_alien_direction_right 2 - set to false
    gameState.set_alien_direction_right(false);
    EXPECT_EQ(gameState.get_alien_direction_right(), false);

    //set_alien_direction_right 3 - set back to true
    gameState.set_alien_direction_right(true);
    EXPECT_EQ(gameState.get_alien_direction_right(), true);
}

TEST(GameStateTest, SetLevel) {
    GameState gameState;
    
    //set_level 1 - level 1
    gameState.set_level(1);
    EXPECT_EQ(gameState.get_level(), 1);
    float expected_speed_1 = constants::ALIEN_SPEED + (1 - 1) * constants::ACCELERATION;
    EXPECT_FLOAT_EQ(gameState.get_alien_speed(), expected_speed_1);

    //set_level 2 - level 3
    gameState.set_level(3);
    EXPECT_EQ(gameState.get_level(), 3);
    float expected_speed_3 = constants::ALIEN_SPEED + (3 - 1) * constants::ACCELERATION;
    EXPECT_FLOAT_EQ(gameState.get_alien_speed(), expected_speed_3);

    //set_level 3 - level 5
    gameState.set_level(5);
    EXPECT_EQ(gameState.get_level(), 5);
    float expected_speed_5 = constants::ALIEN_SPEED + (5 - 1) * constants::ACCELERATION;
    EXPECT_FLOAT_EQ(gameState.get_alien_speed(), expected_speed_5);
}

TEST(GameStateTest, SetLevelSpeedIncrease) {
    GameState gameState;
    
    //set_level 4 - verify speed increases with level
    gameState.set_level(1);
    float speed_level_1 = gameState.get_alien_speed();
    
    //set_level 5 - higher level should have higher speed
    gameState.set_level(2);
    float speed_level_2 = gameState.get_alien_speed();
    EXPECT_GT(speed_level_2, speed_level_1);
    
    //set_level 6 - even higher level should have even higher speed
    gameState.set_level(10);
    float speed_level_10 = gameState.get_alien_speed();
    EXPECT_GT(speed_level_10, speed_level_2);
}
