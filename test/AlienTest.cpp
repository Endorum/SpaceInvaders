#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "../src/model/Laser.hpp"
#include "../src/model/Alien.hpp"

TEST(AlienTest, AddLaser) {
    Alien alien = Alien(100.0f, 100.0f);
    Laser laser = Laser(100.0f, 90.0f);

    //Test call add_laser 1
    alien.add_laser(laser);
    EXPECT_EQ(alien.get_lasers().size(), 1);
}

TEST(AlienTest, RemoveLaserAt) {
    Alien alien = Alien(100.0f, 100.0f);
    Laser laser1 = Laser(100.0f, 90.0f);
    Laser laser2 = Laser(110.0f, 90.0f);
    //Test call add_laser 2
    alien.add_laser(laser1);
    //Test call add_laser 3
    alien.add_laser(laser2);
    EXPECT_EQ(alien.get_lasers().size(), 2);

    //Test call remove_laser_at 1
    alien.remove_laser_at(1);
    EXPECT_EQ(alien.get_lasers().size(), 1);
    EXPECT_EQ(alien.get_lasers()[0].get_pos_x(), 100.0f);

    //Test call remove_laser_at 2
    alien.remove_laser_at(0);
    EXPECT_EQ(alien.get_lasers().size(), 0);

    //Test call remove_laser_at 3 (invalid index)
    alien.remove_laser_at(0);
    EXPECT_EQ(alien.get_lasers().size(), 0);
}