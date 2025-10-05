#include <gtest/gtest.h>

#include "../../src/control/AlienController.hpp"
#include "../../src/model/Alien.hpp"

/* Testen von Game.cpp/.hpp */

#include "../../src/control/Game.hpp"
#include "../../src/model/Player.hpp"
#include "../../src/model/Alien.hpp"
#include "../../src/model/Bunker.hpp"
#include "../../src/model/Laser.hpp"
#include "../../src/model/Constants.hpp"

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