#include "../../src/control/AlienController.hpp"
#include <gtest/gtest.h>
#include <gmock/gmock.h>

// Dummy-Werte für Tests
const float START_X = 100.f;
const float START_Y = 50.f;


TEST(AlienControllerTest, ShootLaserAddsLaser){
  Alien alien(START_X, START_Y);
  AlienController controller(alien);

  EXPECT_EQ(alien.get_lasers().size(), 0);

  controller.shoot_laser();

  ASSERT_EQ(alien.get_lasers().size(), 1);
  
}

TEST(AlienControllerTest, LaserPosition){
  Alien alien(START_X, START_Y);
  AlienController controller(alien);

  controller.shoot_laser();

  float alienHeight = alien.get_height();

  auto& laser = alien.get_lasers().at(0);
  EXPECT_FLOAT_EQ(laser.get_pos_x(), START_X);
  EXPECT_FLOAT_EQ(laser.get_pos_y(), START_Y + alienHeight / 2.f);
}

TEST(AlienControllerTest, MultipleLasers){
  Alien alien(START_X, START_Y);
  AlienController controller(alien);

  controller.shoot_laser();
  controller.shoot_laser();

  ASSERT_EQ(alien.get_lasers().size(), 2);
}

TEST(AlienControllerTest, DestroyLaserAtRemovesCorrectLaser){
  Alien alien(START_X, START_Y);
  AlienController controller(alien);

  controller.shoot_laser();
  controller.shoot_laser();
  controller.shoot_laser();

  ASSERT_EQ(alien.get_lasers().size(), 3);

  controller.destroy_laser_at(1);

  ASSERT_EQ(alien.get_lasers().size(), 2);
  // Remaining lasers should be at index 0 and 1
  EXPECT_FLOAT_EQ(alien.get_lasers()[0].get_pos_x(), START_X);
  EXPECT_FLOAT_EQ(alien.get_lasers()[1].get_pos_x(), START_X);
}

TEST(AlienControllerTest, DestroyLaserAtInvalidIndexDoesNothing){
  Alien alien(START_X, START_Y);
  AlienController controller(alien);

  controller.shoot_laser();

  ASSERT_EQ(alien.get_lasers().size(), 1);

  // Try to remove out-of-bounds index
  controller.destroy_laser_at(5);

  ASSERT_EQ(alien.get_lasers().size(), 1);
}

TEST(AlienControllerTest, AlienLasersAreIndependent){
  Alien alien1(START_X, START_Y);
  Alien alien2(START_X + 50, START_Y + 50);
  AlienController controller1(alien1);
  AlienController controller2(alien2);

  controller1.shoot_laser();
  controller2.shoot_laser();

  ASSERT_EQ(alien1.get_lasers().size(), 1);
  ASSERT_EQ(alien2.get_lasers().size(), 1);

  EXPECT_NE(alien1.get_lasers()[0].get_pos_x(), alien2.get_lasers()[0].get_pos_x());
  EXPECT_NE(alien1.get_lasers()[0].get_pos_y(), alien2.get_lasers()[0].get_pos_y());
}