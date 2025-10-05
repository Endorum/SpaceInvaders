#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "../../src/model/Player.hpp"
#include "../../src/model/Laser.hpp"

TEST(PlayerTest, AddLaser) {
    Player player = Player(100.0f, 100.0f);
    Laser laser1 = Laser(100.0f, 90.0f);
    Laser laser2 = Laser(110.0f, 90.0f);
    Laser laser3 = Laser(120.0f, 90.0f);

    //add_laser 1
    player.add_laser(laser1);
    EXPECT_EQ(player.get_lasers().size(), 1);

    //add_laser 2
    player.add_laser(laser2);
    EXPECT_EQ(player.get_lasers().size(), 2);

    //add_laser 3
    player.add_laser(laser3);
    EXPECT_EQ(player.get_lasers().size(), 3);
}

TEST(PlayerTest, RemoveLaserAt) {
    Player player = Player(100.0f, 100.0f);
    Laser laser1 = Laser(100.0f, 90.0f);
    Laser laser2 = Laser(110.0f, 90.0f);
    Laser laser3 = Laser(120.0f, 90.0f);
    
    player.add_laser(laser1);
    player.add_laser(laser2);
    player.add_laser(laser3);
    EXPECT_EQ(player.get_lasers().size(), 3);

    //remove_laser_at 1 - remove middle laser
    player.remove_laser_at(1);
    EXPECT_EQ(player.get_lasers().size(), 2);
    EXPECT_EQ(player.get_lasers()[0].get_pos_x(), 100.0f);
    EXPECT_EQ(player.get_lasers()[1].get_pos_x(), 120.0f);

    //remove_laser_at 2 - remove first laser
    player.remove_laser_at(0);
    EXPECT_EQ(player.get_lasers().size(), 1);
    EXPECT_EQ(player.get_lasers()[0].get_pos_x(), 120.0f);

    //remove_laser_at 3 - remove last remaining laser
    player.remove_laser_at(0);
    EXPECT_EQ(player.get_lasers().size(), 0);
}

TEST(PlayerTest, RemoveLaserAtInvalidIndex) {
    Player player = Player(100.0f, 100.0f);
    Laser laser = Laser(100.0f, 90.0f);
    player.add_laser(laser);

    //remove_laser_at 4 - invalid index (out of bounds)
    player.remove_laser_at(5);
    EXPECT_EQ(player.get_lasers().size(), 1);

    //remove_laser_at 5 - valid removal
    player.remove_laser_at(0);
    EXPECT_EQ(player.get_lasers().size(), 0);

    //remove_laser_at 6 - invalid index on empty vector
    player.remove_laser_at(0);
    EXPECT_EQ(player.get_lasers().size(), 0);
}
