#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "../../src/model/Positionable.hpp"
#include "../../src/model/Laser.hpp"

// using Laser as a concrete implementation to test Positionable methods

TEST(PositionableTest, MoveHorizontal) {
    Laser laser = Laser(100.0f, 100.0f);

    //move_horizontal 1 - move right within bounds
    bool out_of_bounds = laser.move_horizontal(50.0f);
    EXPECT_FLOAT_EQ(laser.get_pos_x(), 150.0f);
    EXPECT_FLOAT_EQ(laser.get_pos_y(), 100.0f);
    EXPECT_FALSE(out_of_bounds);

    //move_horizontal 2 - move left within bounds
    out_of_bounds = laser.move_horizontal(-30.0f);
    EXPECT_FLOAT_EQ(laser.get_pos_x(), 120.0f);
    EXPECT_FLOAT_EQ(laser.get_pos_y(), 100.0f);
    EXPECT_FALSE(out_of_bounds);

    //move_horizontal 3 - move out of bounds to the right
    out_of_bounds = laser.move_horizontal(constants::VIEW_WIDTH);
    EXPECT_GT(laser.get_pos_x(), constants::VIEW_WIDTH);
    EXPECT_TRUE(out_of_bounds);
}

TEST(PositionableTest, MoveHorizontalOutOfBounds) {
    Laser laser = Laser(100.0f, 100.0f);

    //move_horizontal 4 - move out of bounds to the left
    bool out_of_bounds = laser.move_horizontal(-200.0f);
    EXPECT_LT(laser.get_pos_x(), laser.get_width() / 2);
    EXPECT_TRUE(out_of_bounds);

    //move_horizontal 5 - move from out of bounds back in bounds
    laser = Laser(100.0f, 100.0f);
    laser.move_horizontal(50.0f);
    out_of_bounds = laser.move_horizontal(-40.0f);
    EXPECT_FALSE(out_of_bounds);

    //move_horizontal 6 - zero movement
    float original_x = laser.get_pos_x();
    out_of_bounds = laser.move_horizontal(0.0f);
    EXPECT_FLOAT_EQ(laser.get_pos_x(), original_x);
}

TEST(PositionableTest, MoveVertical) {
    Laser laser = Laser(100.0f, 100.0f);

    //move_vertical 1 - move down within bounds
    bool out_of_bounds = laser.move_vertical(50.0f);
    EXPECT_FLOAT_EQ(laser.get_pos_x(), 100.0f);
    EXPECT_FLOAT_EQ(laser.get_pos_y(), 150.0f);
    EXPECT_FALSE(out_of_bounds);

    //move_vertical 2 - move up within bounds
    out_of_bounds = laser.move_vertical(-30.0f);
    EXPECT_FLOAT_EQ(laser.get_pos_x(), 100.0f);
    EXPECT_FLOAT_EQ(laser.get_pos_y(), 120.0f);
    EXPECT_FALSE(out_of_bounds);

    //move_vertical 3 - move out of bounds downward
    out_of_bounds = laser.move_vertical(constants::VIEW_HEIGHT);
    EXPECT_GT(laser.get_pos_y(), constants::VIEW_HEIGHT);
    EXPECT_TRUE(out_of_bounds);
}

TEST(PositionableTest, MoveVerticalOutOfBounds) {
    Laser laser = Laser(100.0f, 100.0f);

    //move_vertical 4 - move out of bounds upward
    bool out_of_bounds = laser.move_vertical(-200.0f);
    EXPECT_LT(laser.get_pos_y(), laser.get_height() / 2);
    EXPECT_TRUE(out_of_bounds);

    //move_vertical 5 - move from out of bounds back in bounds
    laser = Laser(100.0f, 100.0f);
    laser.move_vertical(50.0f);
    out_of_bounds = laser.move_vertical(-40.0f);
    EXPECT_FALSE(out_of_bounds);

    //move_vertical 6 - zero movement
    float original_y = laser.get_pos_y();
    out_of_bounds = laser.move_vertical(0.0f);
    EXPECT_FLOAT_EQ(laser.get_pos_y(), original_y);
}

TEST(PositionableTest, InBoundsHorizontal) {
    //in_bounds_horizontal 1 - position within bounds
    Laser laser1 = Laser(100.0f, 100.0f);
    EXPECT_TRUE(laser1.in_bounds_horizontal());

    //in_bounds_horizontal 2 - position at left edge (out of bounds)
    Laser laser2 = Laser(0.0f, 100.0f);
    EXPECT_FALSE(laser2.in_bounds_horizontal());

    //in_bounds_horizontal 3 - position at right edge (out of bounds)
    Laser laser3 = Laser(constants::VIEW_WIDTH, 100.0f);
    EXPECT_FALSE(laser3.in_bounds_horizontal());
}

TEST(PositionableTest, InBoundsHorizontalEdgeCases) {
    //in_bounds_horizontal 4 - just inside left bound
    float half_width = 1.0f / 2;
    Laser laser1 = Laser(half_width + 1.0f, 100.0f);
    EXPECT_TRUE(laser1.in_bounds_horizontal());

    //in_bounds_horizontal 5 - just inside right bound
    Laser laser2 = Laser(constants::VIEW_WIDTH - half_width - 1.0f, 100.0f);
    EXPECT_TRUE(laser2.in_bounds_horizontal());

    //in_bounds_horizontal 6 - center position
    Laser laser3 = Laser(constants::VIEW_WIDTH / 2, 100.0f);
    EXPECT_TRUE(laser3.in_bounds_horizontal());
}

TEST(PositionableTest, InBoundsVertical) {
    //in_bounds_vertical 1 - position within bounds
    Laser laser1 = Laser(100.0f, 100.0f);
    EXPECT_TRUE(laser1.in_bounds_vertical());

    //in_bounds_vertical 2 - position at top edge (out of bounds)
    Laser laser2 = Laser(100.0f, 0.0f);
    EXPECT_FALSE(laser2.in_bounds_vertical());

    //in_bounds_vertical 3 - position at bottom edge (out of bounds)
    Laser laser3 = Laser(100.0f, constants::VIEW_HEIGHT);
    EXPECT_FALSE(laser3.in_bounds_vertical());
}

TEST(PositionableTest, InBoundsVerticalEdgeCases) {
    //in_bounds_vertical 4 - just inside top bound
    float half_height = 10.0f / 2;
    Laser laser1 = Laser(100.0f, half_height + 1.0f);
    EXPECT_TRUE(laser1.in_bounds_vertical());

    //in_bounds_vertical 5 - just inside bottom bound
    Laser laser2 = Laser(100.0f, constants::VIEW_HEIGHT - half_height - 1.0f);
    EXPECT_TRUE(laser2.in_bounds_vertical());

    //in_bounds_vertical 6 - center position
    Laser laser3 = Laser(100.0f, constants::VIEW_HEIGHT / 2);
    EXPECT_TRUE(laser3.in_bounds_vertical());
}

TEST(PositionableTest, InBounds) {
    //in_bounds 1 - position fully within bounds
    Laser laser1 = Laser(100.0f, 100.0f);
    EXPECT_TRUE(laser1.in_bounds());

    //in_bounds 2 - position out of bounds horizontally
    Laser laser2 = Laser(0.0f, 100.0f);
    EXPECT_FALSE(laser2.in_bounds());

    //in_bounds 3 - position out of bounds vertically
    Laser laser3 = Laser(100.0f, 0.0f);
    EXPECT_FALSE(laser3.in_bounds());
}

TEST(PositionableTest, InBoundsMultipleConditions) {
    //in_bounds 4 - position out of bounds both horizontally and vertically
    Laser laser1 = Laser(0.0f, 0.0f);
    EXPECT_FALSE(laser1.in_bounds());

    //in_bounds 5 - position at center (definitely in bounds)
    Laser laser2 = Laser(constants::VIEW_WIDTH / 2, constants::VIEW_HEIGHT / 2);
    EXPECT_TRUE(laser2.in_bounds());

    //in_bounds 6 - position near edge but still in bounds
    float half_width = 1.0f / 2;
    float half_height = 10.0f / 2;
    Laser laser3 = Laser(half_width + 1.0f, half_height + 1.0f);
    EXPECT_TRUE(laser3.in_bounds());
}
