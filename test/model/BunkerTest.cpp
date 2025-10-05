#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "../../src/model/Bunker.hpp"

TEST(BunkerTest, SetHealth) {
    Bunker bunker = Bunker(100.0f, 100.0f);

    //set_health 1 - normal value
    bunker.set_health(5);
    EXPECT_EQ(bunker.get_health(), 5);

    //set_health 2 - negative value should clamp to 0
    bunker.set_health(-5);
    EXPECT_EQ(bunker.get_health(), 0);

    //set_health 3 - value above 10 should clamp to 10
    bunker.set_health(15);
    EXPECT_EQ(bunker.get_health(), 10);
}

TEST(BunkerTest, SetHealthEdgeCases) {
    Bunker bunker = Bunker(100.0f, 100.0f);

    //set_health 4 - minimum valid value
    bunker.set_health(0);
    EXPECT_EQ(bunker.get_health(), 0);

    //set_health 5 - maximum valid value
    bunker.set_health(10);
    EXPECT_EQ(bunker.get_health(), 10);

    //set_health 6 - value within range
    bunker.set_health(7);
    EXPECT_EQ(bunker.get_health(), 7);
}
