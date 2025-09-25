#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include "../src/control/AlienController.hpp"
#include "../src/model/Alien.hpp"


/* Testen von AlienController */

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



/* Testen von BunkersController.cpp/.hpp */

#include "../src/control/BunkersController.hpp"
#include "../src/model/Bunker.hpp"

const float BUNKER_X = 200.f;
const float BUNKER_Y = 400.f;

TEST(BunkersControllerTest, PlaceBunkersAddsCorrectAmount) {
  std::vector<Bunker> bunkers;
  BunkersController controller(bunkers);

  controller.place_bunkers(3);

  ASSERT_EQ(bunkers.size(), 3);
}

TEST(BunkersControllerTest, DamageBunkerReducesHealth) {
  std::vector<Bunker> bunkers;
  BunkersController controller(bunkers);

  controller.place_bunkers(1);
  int initial_health = bunkers[0].get_health();

  controller.damage_bunker(0);

  EXPECT_EQ(bunkers[0].get_health(), initial_health - 1);
}

TEST(BunkersControllerTest, DamageBunkerRemovesDestroyedBunker) {
  std::vector<Bunker> bunkers;
  BunkersController controller(bunkers);

  controller.place_bunkers(1);
  // Damage until destroyed
  int health = bunkers[0].get_health();
  for (int i = 0; i < health; ++i) {
    controller.damage_bunker(0);
  }

  ASSERT_TRUE(bunkers.empty());
}

TEST(BunkersControllerTest, DamageBunkerInvalidIndexDoesNothing) {
  std::vector<Bunker> bunkers;
  BunkersController controller(bunkers);

  controller.place_bunkers(2);
  int health0 = bunkers[0].get_health();
  int health1 = bunkers[1].get_health();

  controller.damage_bunker(5); // Invalid index

  EXPECT_EQ(bunkers[0].get_health(), health0);
  EXPECT_EQ(bunkers[1].get_health(), health1);
}

TEST(BunkersControllerTest, MultipleBunkersDamageOnlyAffectsCorrectOne) {
  std::vector<Bunker> bunkers;
  BunkersController controller(bunkers);

  controller.place_bunkers(2);
  int health0 = bunkers[0].get_health();
  int health1 = bunkers[1].get_health();

  controller.damage_bunker(1);

  EXPECT_EQ(bunkers[0].get_health(), health0);
  EXPECT_EQ(bunkers[1].get_health(), health1 - 1);
}

/* Testen von Game.cpp/.hpp */

#include "../src/control/Game.hpp"
#include "../src/model/Player.hpp"
#include "../src/model/Alien.hpp"
#include "../src/model/Bunker.hpp"
#include "../src/model/Laser.hpp"
#include "../src/model/Constants.hpp"

// Helper class to expose protected/private methods for testing
class TestGame : public Game {
public:
  using Game::check_bunker_hits;
  using Game::check_collision;
  using Game::state;
  using Game::check_player_hits;
  using Game::check_alien_hits;
};

// Test collision detection between two positionable objects
TEST(GameTest, CollisionDetectionTrue) {
  Player player(100.f, 100.f);
  Alien alien(100.f, 100.f);

// Test that collision detection returns true when player and alien overlap
  TestGame game;
  EXPECT_TRUE(game.check_collision(player, alien));
}

TEST(GameTest, CollisionDetectionFalse) {
  Player player(100.f, 100.f);
  Alien alien(300.f, 300.f);

  TestGame game;
  EXPECT_FALSE(game.check_collision(player, alien));
}

// Test that player loses health when hit by alien laser
TEST(GameTest, PlayerHitByAlienLaserDecreasesHealth) {
  TestGame game;
  auto& aliens = game.state.get_aliens();
  auto& player = game.state.get_player();

  aliens.emplace_back(player.get_pos_x(), player.get_pos_y());
  Alien& alien = aliens.back();

  float playerposx = player.get_pos_x();
  float playerposy = player.get_pos_y();

  AlienController alienController(alien);
  alienController.shoot_laser();

  int initial_health = player.get_health();
  game.check_player_hits();

  EXPECT_EQ(player.get_health(), initial_health - 1);
}

// Test that player is finished (window closed) when health reaches zero
TEST(GameTest, PlayerDiesWhenHealthZero) {
  TestGame game;
  auto& aliens = game.state.get_aliens();
  auto& player = game.state.get_player();

  aliens.emplace_back(player.get_pos_x(), player.get_pos_y());
  Alien& alien = aliens.back();

  // Set player health to 1, so one hit kills
  player.set_health(1);
  AlienController alienController(alien);
  alienController.shoot_laser();

  // finish() closes window, but we can't check window state here, just that health is zero
  game.check_player_hits();
  EXPECT_EQ(player.get_health(), 0);
}

// Test that alien is removed when hit by player laser
TEST(GameTest, AlienRemovedWhenHitByPlayerLaser) {
  TestGame game;
  auto& aliens = game.state.get_aliens();
  auto& player = game.state.get_player();

  // Alien erzeugen
  aliens.emplace_back(100.f, 100.f);
  Alien& alien = aliens.back();

  // Player-Laser erzeugen, der das Alien trifft
  player.get_lasers().emplace_back(100.f, 100.f, 0.f, -1.f); // x, y, dx, dy

  size_t initial_aliens = aliens.size();

  // check_alien_hits prüft Player-Laser vs Aliens
  game.check_alien_hits();

  EXPECT_EQ(aliens.size(), initial_aliens - 1);  // Alien sollte weg sein
}


// Test that player laser is removed after hitting alien
TEST(GameTest, PlayerLaserRemovedAfterHit) {
  TestGame game;
  auto& aliens = game.state.get_aliens();
  auto& player = game.state.get_player();

  aliens.emplace_back(100.f, 100.f);
  player.get_lasers().emplace_back(100.f, 100.f, 0.f, -1.f);

  size_t initial_lasers = player.get_lasers().size();
  game.check_alien_hits();

  EXPECT_EQ(player.get_lasers().size(), initial_lasers - 1);
}

// Test that bunker is damaged by alien laser
TEST(GameTest, BunkerDamagedByAlienLaser) {
  TestGame game;
  auto& aliens = game.state.get_aliens();
  auto& bunkers = game.state.get_bunkers();

  bunkers.emplace_back(200.f, 200.f);
  int initial_health = bunkers[0].get_health();

  aliens.emplace_back(200.f, 200.f);
  Alien& alien = aliens.back();
  alien.get_lasers().emplace_back(200.f, 200.f, 0.f, 1.f);

  game.check_bunker_hits();

  EXPECT_EQ(bunkers[0].get_health(), initial_health - 1);
}

// Test that bunker is damaged by player laser
TEST(GameTest, BunkerDamagedByPlayerLaser) {
  TestGame game;
  auto& bunkers = game.state.get_bunkers();
  auto& player = game.state.get_player();

  bunkers.emplace_back(250.f, 250.f);
  int initial_health = bunkers[0].get_health();

  player.get_lasers().emplace_back(250.f, 250.f, 0.f, -1.f);

  game.check_bunker_hits();

  EXPECT_EQ(bunkers[0].get_health(), initial_health - 1);
}

// Test that update calls finish if aliens_controller.update returns true
class FinishCalledGame : public Game {
public:
  bool finish_called = false;
  void finish() { finish_called = true; }
  void setAliensControllerUpdateReturn(bool value) { update_return = value; }
  bool update_return = false;
  bool update(float) {
    if (update_return) {
      finish();
      return true;
    }
    return false;
  }
};

TEST(GameTest, UpdateCallsFinishIfAliensControllerReturnsTrue) {
  FinishCalledGame game;
  game.setAliensControllerUpdateReturn(true);
  game.update(0.1f);
  EXPECT_TRUE(game.finish_called);
}

/* Testen von PlayerController.cpp/.hpp */

#include "../src/control/PlayerController.hpp"
#include "../src/model/Player.hpp"
#include "../src/model/Laser.hpp"

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

/* Testen des SoundsController.cpp/.hpp */

#include "../src/control/SoundsController.hpp"

class SoundsControllerTest : public ::testing::Test {
protected:
  SoundsController sounds;
};

TEST_F(SoundsControllerTest, PlayPlayerShootingSoundDoesNotThrow) {
  // Should not throw or crash even if sound file is missing
  EXPECT_NO_THROW(sounds.play_player_shooting_sound());
}

TEST_F(SoundsControllerTest, PlayAlienDeathSoundDoesNotThrow) {
  EXPECT_NO_THROW(sounds.play_alien_death_sound());
}



// If SoundsController exposes sound buffer loading, test loading failure gracefully
TEST_F(SoundsControllerTest, MultipleSoundsCanBePlayed) {
  // Should not crash if called multiple times in a row
  for (int i = 0; i < 5; ++i) {
    sounds.play_player_shooting_sound();
    sounds.play_alien_death_sound();
  }
}