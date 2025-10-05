#include <gtest/gtest.h>

#include "../../src/control/PlayerController.hpp"
#include "../../src/model/Player.hpp"
#include "../../src/model/Laser.hpp"

const float PLAYER_START_X = 300.f;
const float PLAYER_START_Y = 500.f;

TEST(PlayerControllerTest, MoveRightIncreasesX) {
  Player player(PLAYER_START_X, PLAYER_START_Y);
  PlayerController controller(player);

  float initial_x = player.get_pos_x();
  controller.move_right();
  EXPECT_GT(player.get_pos_x(), initial_x);
}

TEST(PlayerControllerTest, MoveLeftDecreasesX) {
  Player player(PLAYER_START_X, PLAYER_START_Y);
  PlayerController controller(player);

  float initial_x = player.get_pos_x();
  controller.move_left();
  EXPECT_LT(player.get_pos_x(), initial_x);
}

TEST(PlayerControllerTest, ShootLaserAddsLaser) {
  Player player(PLAYER_START_X, PLAYER_START_Y);
  PlayerController controller(player);

  EXPECT_EQ(player.get_lasers().size(), 0);
  controller.shoot_laser();
  EXPECT_EQ(player.get_lasers().size(), 1);
}

TEST(PlayerControllerTest, ShootLaserPosition) {
  Player player(PLAYER_START_X, PLAYER_START_Y);
  PlayerController controller(player);

  controller.shoot_laser();
  auto& laser = player.get_lasers().at(0);
  EXPECT_FLOAT_EQ(laser.get_pos_x(), PLAYER_START_X);
  EXPECT_FLOAT_EQ(laser.get_pos_y(), PLAYER_START_Y - 20.f);
}

TEST(PlayerControllerTest, DecreaseHealthReducesHealth) {
  Player player(PLAYER_START_X, PLAYER_START_Y);
  PlayerController controller(player);

  int initial_health = player.get_health();
  controller.decrease_health();
  EXPECT_EQ(player.get_health(), initial_health - 1);
}

TEST(PlayerControllerTest, IncreaseScoreAddsPoints) {
  Player player(PLAYER_START_X, PLAYER_START_Y);
  PlayerController controller(player);

  int initial_score = player.get_score();
  controller.increase_score(50);
  EXPECT_EQ(player.get_score(), initial_score + 50);
}

TEST(PlayerControllerTest, UpdateMovesLasers) {
  Player player(PLAYER_START_X, PLAYER_START_Y);
  PlayerController controller(player);

  controller.shoot_laser();
  float initial_y = player.get_lasers()[0].get_pos_y();
  controller.update(0.1f);
  EXPECT_LT(player.get_lasers()[0].get_pos_y(), initial_y);
}

TEST(PlayerControllerTest, LaserRemovedWhenOutOfBounds) {
  Player player(PLAYER_START_X, PLAYER_START_Y);
  PlayerController controller(player);

  controller.shoot_laser();
  // Move laser far out of bounds
  player.get_lasers()[0].set_pos_y(-1000.f);
  controller.update(0.1f);
  EXPECT_TRUE(player.get_lasers().empty());
}