#include <gtest/gtest.h>

#include "../../src/control/BunkersController.hpp"
#include "../../src/model/Bunker.hpp"

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
