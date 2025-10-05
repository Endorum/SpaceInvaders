#include <gtest/gtest.h>

#include "../../src/control/SoundsController.hpp"

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