#include "CultsBoard.hh"
#include "Factions.hh"
#include "gtest/gtest.h"
#include "MockIPowerUser.hh"
#include "NullPowerUser.hh" // Stub
#include <iostream>

using namespace std;
using ::testing::Return;

class CultsBoardTest : public ::testing::Test
{
protected:
    virtual void SetUp() { }
    virtual void TearDown() { }
protected:
   MockIPowerUser mockPowerUser;
};

const unsigned int NOT_CALLED = 0;
const unsigned int CALLED_ONCE = 1;

const unsigned int CULT_ZERO = 0;
const unsigned int CULT_ONE = 1;
const unsigned int CULT_TWO = 2;
const unsigned int CULT_THREE = 3;
const unsigned int CULT_FOUR = 4;
const unsigned int CULT_FIVE = 5;
const unsigned int CULT_SIX = 6;
const unsigned int CULT_SEVEN = 7;
const unsigned int CULT_EIGHT = 8;
const unsigned int CULT_NINE = 9;
const unsigned int CULT_TEN = 10;

TEST_F(CultsBoardTest, adding_faction_should_success_with_2000_as_start_values)
{
    CultsBoard cultsBoard;

    EXPECT_CALL(mockPowerUser, addPower(::testing::_)).Times(NOT_CALLED);
    EXPECT_CALL(mockPowerUser, getNumberOfKeys()).Times(NOT_CALLED);
    ASSERT_TRUE(cultsBoard.addFaction(eChaosMagicians, mockPowerUser, CULT_TWO, CULT_ZERO, CULT_ZERO, CULT_ZERO));

    ASSERT_EQ(CULT_TWO, cultsBoard.getCultValue(eChaosMagicians, eFire));
    ASSERT_EQ(CULT_ZERO, cultsBoard.getCultValue(eChaosMagicians, eWater));
    ASSERT_EQ(CULT_ZERO, cultsBoard.getCultValue(eChaosMagicians, eEarth));
    ASSERT_EQ(CULT_ZERO, cultsBoard.getCultValue(eChaosMagicians, eAir));
}

TEST_F(CultsBoardTest, adding_the_same_faction_again_should_not_change_the_cult_values)
{
    CultsBoard cultsBoard;
    ASSERT_TRUE(cultsBoard.addFaction(eChaosMagicians, mockPowerUser, CULT_TWO, CULT_ZERO, CULT_ZERO, CULT_ZERO));

    ASSERT_EQ(CULT_TWO, cultsBoard.getCultValue(eChaosMagicians, eFire));
    ASSERT_EQ(CULT_ZERO, cultsBoard.getCultValue(eChaosMagicians, eWater));
    ASSERT_EQ(CULT_ZERO, cultsBoard.getCultValue(eChaosMagicians, eEarth));
    ASSERT_EQ(CULT_ZERO, cultsBoard.getCultValue(eChaosMagicians, eAir));

    EXPECT_CALL(mockPowerUser, addPower(CULT_THREE)).Times(CALLED_ONCE);
    ASSERT_EQ(CULT_THREE, cultsBoard.increaseCultValue(eChaosMagicians, eFire, CULT_THREE));
    EXPECT_CALL(mockPowerUser, addPower(CULT_ONE)).Times(CALLED_ONCE);
    ASSERT_EQ(CULT_THREE, cultsBoard.increaseCultValue(eChaosMagicians, eWater, 3));
    EXPECT_CALL(mockPowerUser, addPower(1)).Times(1);
    ASSERT_EQ(CULT_THREE, cultsBoard.increaseCultValue(eChaosMagicians, eEarth, 3));
    EXPECT_CALL(mockPowerUser, addPower(1)).Times(1);
    ASSERT_EQ(CULT_THREE, cultsBoard.increaseCultValue(eChaosMagicians, eAir, 3));

    ASSERT_EQ(CULT_FIVE, cultsBoard.getCultValue(eChaosMagicians, eFire));
    ASSERT_EQ(CULT_THREE, cultsBoard.getCultValue(eChaosMagicians, eWater));
    ASSERT_EQ(CULT_THREE, cultsBoard.getCultValue(eChaosMagicians, eEarth));
    ASSERT_EQ(CULT_THREE, cultsBoard.getCultValue(eChaosMagicians, eAir));

    ASSERT_FALSE(cultsBoard.addFaction(eChaosMagicians, mockPowerUser, 2, 0, 0, 0));

    ASSERT_EQ(CULT_FIVE, cultsBoard.getCultValue(eChaosMagicians, eFire));
    ASSERT_EQ(CULT_THREE, cultsBoard.getCultValue(eChaosMagicians, eWater));
    ASSERT_EQ(CULT_THREE, cultsBoard.getCultValue(eChaosMagicians, eEarth));
    ASSERT_EQ(CULT_THREE, cultsBoard.getCultValue(eChaosMagicians, eAir));
}

TEST_F(CultsBoardTest, increasing_value_before_adding_faction_should_not_work)
{
    CultsBoard cultsBoard;
    NullPowerUser nullPowerUser;
    ASSERT_EQ(CULT_ZERO, cultsBoard.increaseCultValue(eChaosMagicians, eWater, 2));
    ASSERT_EQ(CULT_ZERO, cultsBoard.getCultValue(eChaosMagicians, eWater));

    ASSERT_TRUE(cultsBoard.addFaction(eChaosMagicians, nullPowerUser, 2, 0, 0, 0));

    ASSERT_EQ(CULT_TWO, cultsBoard.increaseCultValue(eChaosMagicians, eWater, 2));
    ASSERT_EQ(CULT_TWO, cultsBoard.getCultValue(eChaosMagicians, eWater));
}

TEST_F(CultsBoardTest, increasing_value_for_1_faction_by_2_on_one_track)
{
    CultsBoard cultsBoard;
    NullPowerUser nullPowerUser;

    ASSERT_TRUE(cultsBoard.addFaction(eFakirs, nullPowerUser, 0, 1, 0, 1));

    ASSERT_EQ(CULT_TWO, cultsBoard.increaseCultValue(eFakirs, eFire, 2));
    ASSERT_EQ(CULT_TWO, cultsBoard.getCultValue(eFakirs, eFire));
}

TEST_F(CultsBoardTest, increasing_value_by_2_on_one_track_for_ChaosMagicians)
{
    CultsBoard cultsBoard;
    ASSERT_TRUE(cultsBoard.addFaction(eChaosMagicians, mockPowerUser, 2, 0, 0, 0));

    EXPECT_CALL(mockPowerUser, addPower(3)).Times(1);
    ASSERT_EQ(CULT_THREE, cultsBoard.increaseCultValue(eChaosMagicians, eFire, 3));
    ASSERT_EQ(CULT_FIVE, cultsBoard.getCultValue(eChaosMagicians, eFire));

    EXPECT_CALL(mockPowerUser, addPower(2)).Times(1);
    ASSERT_EQ(CULT_TWO, cultsBoard.increaseCultValue(eChaosMagicians, eFire, 2));
    ASSERT_EQ(CULT_SEVEN, cultsBoard.getCultValue(eChaosMagicians, eFire));

    ASSERT_EQ(CULT_TWO, cultsBoard.increaseCultValue(eChaosMagicians, eFire, 2));
    ASSERT_EQ(CULT_NINE, cultsBoard.getCultValue(eChaosMagicians, eFire));

    EXPECT_CALL(mockPowerUser, addPower(3)).Times(1);
    EXPECT_CALL(mockPowerUser, getNumberOfKeys()).Times(1).WillOnce(Return(1));
    ASSERT_EQ(CULT_ONE, cultsBoard.increaseCultValue(eChaosMagicians, eFire, 1));
    ASSERT_EQ(CULT_TEN, cultsBoard.getCultValue(eChaosMagicians, eFire));
}

TEST_F(CultsBoardTest, increasing_value_for_1_faction_by_1_on_one_track)
{
    CultsBoard cultsBoard;
    NullPowerUser nullPowerUser;
    ASSERT_TRUE(cultsBoard.addFaction(eFakirs, nullPowerUser, 0, 1, 0, 1));
    ASSERT_EQ(CULT_ONE, cultsBoard.increaseCultValue(eFakirs, eFire, 1));
    ASSERT_EQ(CULT_ONE, cultsBoard.getCultValue(eFakirs, eFire));
}

TEST_F(CultsBoardTest, increasing_value_for_1_faction_by_3_on_one_track)
{
    CultsBoard cultsBoard;
    NullPowerUser nullPowerUser;
    ASSERT_TRUE(cultsBoard.addFaction(eFakirs, nullPowerUser, 0, 1, 0, 1));

    ASSERT_EQ(CULT_THREE, cultsBoard.increaseCultValue(eFakirs, eFire, 3));
    ASSERT_EQ(CULT_THREE, cultsBoard.getCultValue(eFakirs, eFire));
}

TEST_F(CultsBoardTest, increasing_value_for_1_faction_by_1_then_2_on_one_track)
{
    CultsBoard cultsBoard;
    NullPowerUser nullPowerUser;
    ASSERT_TRUE(cultsBoard.addFaction(eFakirs, nullPowerUser, 0, 1, 0, 1));

    ASSERT_EQ(CULT_ONE, cultsBoard.increaseCultValue(eFakirs, eFire, 1));
    ASSERT_EQ(CULT_ONE, cultsBoard.getCultValue(eFakirs, eFire));

    ASSERT_EQ(CULT_TWO, cultsBoard.increaseCultValue(eFakirs, eFire, 2));
    ASSERT_EQ(CULT_THREE, cultsBoard.getCultValue(eFakirs, eFire));
}

TEST_F(CultsBoardTest, increasing_value_for_1_faction_by_2_then_1_on_one_track)
{
    CultsBoard cultsBoard;
    NullPowerUser nullPowerUser;
    ASSERT_TRUE(cultsBoard.addFaction(eFakirs, nullPowerUser, 0, 1, 0, 1));

    ASSERT_EQ(CULT_TWO, cultsBoard.increaseCultValue(eFakirs, eFire, 2));
    ASSERT_EQ(CULT_TWO, cultsBoard.getCultValue(eFakirs, eFire));

    ASSERT_EQ(CULT_ONE, cultsBoard.increaseCultValue(eFakirs, eFire, 1));
    ASSERT_EQ(CULT_THREE, cultsBoard.getCultValue(eFakirs, eFire));
}

TEST_F(CultsBoardTest, increasing_value_for_1_faction_by_2_then_1_on_two_tracks)
{
    CultsBoard cultsBoard;
    NullPowerUser nullPowerUser;
    ASSERT_TRUE(cultsBoard.addFaction(eFakirs, nullPowerUser, 0, 1, 0, 1));

    ASSERT_EQ(CULT_TWO, cultsBoard.increaseCultValue(eFakirs, eFire, 2));
    ASSERT_EQ(CULT_TWO, cultsBoard.getCultValue(eFakirs, eFire));
    ASSERT_EQ(CULT_ONE, cultsBoard.getCultValue(eFakirs, eWater));

    ASSERT_EQ(CULT_ONE, cultsBoard.increaseCultValue(eFakirs, eWater, 1));
    ASSERT_EQ(CULT_TWO, cultsBoard.getCultValue(eFakirs, eWater));
    ASSERT_EQ(CULT_TWO, cultsBoard.getCultValue(eFakirs, eFire));

    ASSERT_EQ(CULT_ONE, cultsBoard.increaseCultValue(eFakirs, eFire, 1));
    ASSERT_EQ(CULT_THREE, cultsBoard.getCultValue(eFakirs, eFire));
    ASSERT_EQ(CULT_TWO, cultsBoard.getCultValue(eFakirs, eWater));

    ASSERT_EQ(CULT_TWO, cultsBoard.increaseCultValue(eFakirs, eWater, 2));
    ASSERT_EQ(CULT_THREE, cultsBoard.getCultValue(eFakirs, eFire));
    ASSERT_EQ(CULT_FOUR, cultsBoard.getCultValue(eFakirs, eWater));
}

TEST_F(CultsBoardTest, increasing_value_for_2_factions_by_2_on_one_track)
{
    CultsBoard cultsBoard;
    NullPowerUser nullPowerUser;
    ASSERT_TRUE(cultsBoard.addFaction(eFakirs, nullPowerUser, 0, 1, 0, 1));
    ASSERT_TRUE(cultsBoard.addFaction(eChaosMagicians, nullPowerUser, 2, 0, 0, 0));

    ASSERT_EQ(CULT_TWO, cultsBoard.increaseCultValue(eFakirs, eFire, 2));
    ASSERT_EQ(CULT_TWO, cultsBoard.getCultValue(eFakirs, eFire));
    ASSERT_EQ(CULT_TWO, cultsBoard.getCultValue(eChaosMagicians, eFire));

    ASSERT_EQ(CULT_TWO, cultsBoard.increaseCultValue(eChaosMagicians, eFire, 2));
    ASSERT_EQ(CULT_TWO, cultsBoard.getCultValue(eFakirs, eFire));
    ASSERT_EQ(CULT_FOUR, cultsBoard.getCultValue(eChaosMagicians, eFire));
}

TEST_F(CultsBoardTest, increasing_value_for_2_factions_by_2_then_1_on_two_tracks)
{
    CultsBoard cultsBoard;
    NullPowerUser nullPowerUser;
    ASSERT_TRUE(cultsBoard.addFaction(eFakirs, nullPowerUser, 0, 0, 0, 0));
    ASSERT_TRUE(cultsBoard.addFaction(eChaosMagicians, nullPowerUser, 0, 0, 0, 0));

    ASSERT_EQ(CULT_TWO, cultsBoard.increaseCultValue(eFakirs, eFire, 2));
    ASSERT_EQ(CULT_TWO, cultsBoard.getCultValue(eFakirs, eFire));
    ASSERT_EQ(CULT_ZERO, cultsBoard.getCultValue(eFakirs, eWater));
    ASSERT_EQ(CULT_ZERO, cultsBoard.getCultValue(eChaosMagicians, eFire));
    ASSERT_EQ(CULT_ZERO, cultsBoard.getCultValue(eChaosMagicians, eWater));

    ASSERT_EQ(CULT_TWO, cultsBoard.increaseCultValue(eChaosMagicians, eWater, 2));
    ASSERT_EQ(CULT_TWO, cultsBoard.getCultValue(eFakirs, eFire));
    ASSERT_EQ(CULT_ZERO, cultsBoard.getCultValue(eFakirs, eWater));
    ASSERT_EQ(CULT_ZERO, cultsBoard.getCultValue(eChaosMagicians, eFire));
    ASSERT_EQ(CULT_TWO, cultsBoard.getCultValue(eChaosMagicians, eWater));

    ASSERT_EQ(CULT_ONE, cultsBoard.increaseCultValue(eFakirs, eWater, 1));
    ASSERT_EQ(CULT_TWO, cultsBoard.getCultValue(eFakirs, eFire));
    ASSERT_EQ(CULT_ONE, cultsBoard.getCultValue(eFakirs, eWater));
    ASSERT_EQ(CULT_ZERO, cultsBoard.getCultValue(eChaosMagicians, eFire));
    ASSERT_EQ(CULT_TWO, cultsBoard.getCultValue(eChaosMagicians, eWater));

    ASSERT_EQ(CULT_ONE, cultsBoard.increaseCultValue(eChaosMagicians, eFire, 1));
    ASSERT_EQ(CULT_TWO, cultsBoard.getCultValue(eFakirs, eFire));
    ASSERT_EQ(CULT_ONE, cultsBoard.getCultValue(eFakirs, eWater));
    ASSERT_EQ(CULT_ONE, cultsBoard.getCultValue(eChaosMagicians, eFire));
    ASSERT_EQ(CULT_TWO, cultsBoard.getCultValue(eChaosMagicians, eWater));

    ASSERT_EQ(CULT_ONE, cultsBoard.increaseCultValue(eFakirs, eFire, 1));
    ASSERT_EQ(CULT_THREE, cultsBoard.getCultValue(eFakirs, eFire));
    ASSERT_EQ(CULT_ONE, cultsBoard.getCultValue(eFakirs, eWater));
    ASSERT_EQ(CULT_ONE, cultsBoard.getCultValue(eChaosMagicians, eFire));
    ASSERT_EQ(CULT_TWO, cultsBoard.getCultValue(eChaosMagicians, eWater));

    ASSERT_EQ(CULT_ONE, cultsBoard.increaseCultValue(eChaosMagicians, eWater, 1));
    ASSERT_EQ(CULT_THREE, cultsBoard.getCultValue(eFakirs, eFire));
    ASSERT_EQ(CULT_ONE, cultsBoard.getCultValue(eFakirs, eWater));
    ASSERT_EQ(CULT_ONE, cultsBoard.getCultValue(eChaosMagicians, eFire));
    ASSERT_EQ(CULT_THREE, cultsBoard.getCultValue(eChaosMagicians, eWater));

    ASSERT_EQ(CULT_TWO, cultsBoard.increaseCultValue(eFakirs, eWater, 2));
    ASSERT_EQ(CULT_THREE, cultsBoard.getCultValue(eFakirs, eFire));
    ASSERT_EQ(CULT_THREE, cultsBoard.getCultValue(eFakirs, eWater));
    ASSERT_EQ(CULT_ONE, cultsBoard.getCultValue(eChaosMagicians, eFire));
    ASSERT_EQ(CULT_THREE, cultsBoard.getCultValue(eChaosMagicians, eWater));

    ASSERT_EQ(CULT_TWO, cultsBoard.increaseCultValue(eChaosMagicians, eFire, 2));
    ASSERT_EQ(CULT_THREE, cultsBoard.getCultValue(eFakirs, eFire));
    ASSERT_EQ(CULT_THREE, cultsBoard.getCultValue(eFakirs, eWater));
    ASSERT_EQ(CULT_THREE, cultsBoard.getCultValue(eChaosMagicians, eFire));
    ASSERT_EQ(CULT_THREE, cultsBoard.getCultValue(eChaosMagicians, eWater));
}

TEST_F(CultsBoardTest, increasing_value_for_3_factions_by_2_on_one_track)
{
    CultsBoard cultsBoard;
    NullPowerUser nullPowerUser;
    ASSERT_TRUE(cultsBoard.addFaction(eFakirs, nullPowerUser, 0, 0, 0, 0));
    ASSERT_TRUE(cultsBoard.addFaction(eChaosMagicians, nullPowerUser, 0, 0, 0, 0));
    ASSERT_TRUE(cultsBoard.addFaction(eWitches, nullPowerUser, 0, 0, 0, 0));

    ASSERT_EQ(CULT_TWO, cultsBoard.increaseCultValue(eFakirs, eFire, 2));
    ASSERT_EQ(CULT_TWO, cultsBoard.getCultValue(eFakirs, eFire));
    ASSERT_EQ(CULT_ZERO, cultsBoard.getCultValue(eChaosMagicians, eFire));
    ASSERT_EQ(CULT_ZERO, cultsBoard.getCultValue(eWitches, eFire));

    ASSERT_EQ(CULT_TWO, cultsBoard.increaseCultValue(eChaosMagicians, eFire, 2));
    ASSERT_EQ(CULT_TWO, cultsBoard.getCultValue(eFakirs, eFire));
    ASSERT_EQ(CULT_TWO, cultsBoard.getCultValue(eChaosMagicians, eFire));
    ASSERT_EQ(CULT_ZERO, cultsBoard.getCultValue(eWitches, eFire));

    ASSERT_EQ(CULT_TWO, cultsBoard.increaseCultValue(eWitches, eFire, 2));
    ASSERT_EQ(CULT_TWO, cultsBoard.getCultValue(eFakirs, eFire));
    ASSERT_EQ(CULT_TWO, cultsBoard.getCultValue(eChaosMagicians, eFire));
    ASSERT_EQ(CULT_TWO, cultsBoard.getCultValue(eWitches, eFire));
}

TEST_F(CultsBoardTest, when_no_keys_should_not_move_to_level_10)
{
    CultsBoard cultsBoard;
    ASSERT_TRUE(cultsBoard.addFaction(eWitches, mockPowerUser, 0, 0, 0, 2));

    // Step to value 5
    EXPECT_CALL(mockPowerUser, addPower(3)).Times(1);
    ASSERT_EQ(CULT_THREE, cultsBoard.increaseCultValue(eWitches, eAir, 3));
    ASSERT_EQ(CULT_FIVE, cultsBoard.getCultValue(eWitches, eAir));

    // Step to value 7
    EXPECT_CALL(mockPowerUser, addPower(2)).Times(1);
    ASSERT_EQ(CULT_TWO, cultsBoard.increaseCultValue(eWitches, eAir, 2));
    ASSERT_EQ(CULT_SEVEN, cultsBoard.getCultValue(eWitches, eAir));

    // Step to value 9
    ASSERT_EQ(CULT_TWO, cultsBoard.increaseCultValue(eWitches, eAir, 2));
    ASSERT_EQ(CULT_NINE, cultsBoard.getCultValue(eWitches, eAir));

    // Try to step to value 10 but no success with it.
    const unsigned int NO_KEYS = 0;
    EXPECT_CALL(mockPowerUser, getNumberOfKeys()).Times(1).WillOnce(Return(NO_KEYS));
    ASSERT_EQ(CULT_ZERO, cultsBoard.increaseCultValue(eWitches, eAir, 1));
    ASSERT_EQ(CULT_NINE, cultsBoard.getCultValue(eWitches, eAir));
}

TEST_F(CultsBoardTest, when_stepping_over_level_10_should_result_lvl_10_if_there_is_a_key)
{
    CultsBoard cultsBoard;
    ASSERT_TRUE(cultsBoard.addFaction(eWitches, mockPowerUser, 0, 0, 0, 2));

    // Step to value 5
    EXPECT_CALL(mockPowerUser, addPower(CULT_THREE)).Times(1);
    ASSERT_EQ(CULT_THREE, cultsBoard.increaseCultValue(eWitches, eAir, 3));
    ASSERT_EQ(CULT_FIVE, cultsBoard.getCultValue(eWitches, eAir));

    // Step to value 7
    EXPECT_CALL(mockPowerUser, addPower(CULT_TWO)).Times(1);
    ASSERT_EQ(CULT_TWO, cultsBoard.increaseCultValue(eWitches, eAir, 2));
    ASSERT_EQ(CULT_SEVEN, cultsBoard.getCultValue(eWitches, eAir));

    // Step to value 9
    ASSERT_EQ(CULT_TWO, cultsBoard.increaseCultValue(eWitches, eAir, 2));
    ASSERT_EQ(CULT_NINE, cultsBoard.getCultValue(eWitches, eAir));

    // Try to step to value 10 and it will succeed.
    const unsigned int ONE_KEY = 1;
    EXPECT_CALL(mockPowerUser, getNumberOfKeys()).Times(1).WillOnce(Return(ONE_KEY));
    EXPECT_CALL(mockPowerUser, addPower(CULT_THREE)).Times(1);
    ASSERT_EQ(CULT_ONE, cultsBoard.increaseCultValue(eWitches, eAir, CULT_TWO));
    ASSERT_EQ(CULT_TEN, cultsBoard.getCultValue(eWitches, eAir));
}

TEST_F(CultsBoardTest, one_faction_should_move_lvl10_only_on_one_cult_track_when_1_key_available)
{
    CultsBoard cultsBoard;
    ASSERT_TRUE(cultsBoard.addFaction(eWitches, mockPowerUser, 0, 0, 0, 2));

    // Step to value 5 on Air
    EXPECT_CALL(mockPowerUser, addPower(CULT_THREE)).Times(1);
    ASSERT_EQ(CULT_THREE, cultsBoard.increaseCultValue(eWitches, eAir, 3));
    ASSERT_EQ(CULT_FIVE, cultsBoard.getCultValue(eWitches, eAir));

    // Step to value 7 on Air
    EXPECT_CALL(mockPowerUser, addPower(CULT_TWO)).Times(1);
    ASSERT_EQ(CULT_TWO, cultsBoard.increaseCultValue(eWitches, eAir, 2));
    ASSERT_EQ(CULT_SEVEN, cultsBoard.getCultValue(eWitches, eAir));

    // Step to value 9 on Air
    ASSERT_EQ(CULT_TWO, cultsBoard.increaseCultValue(eWitches, eAir, 2));
    ASSERT_EQ(CULT_NINE, cultsBoard.getCultValue(eWitches, eAir));

    // Try to step to value 10 and it will succeed.
    const unsigned int ONE_KEY = 1;
    EXPECT_CALL(mockPowerUser, getNumberOfKeys()).Times(1).WillOnce(Return(ONE_KEY));
    EXPECT_CALL(mockPowerUser, addPower(CULT_THREE)).Times(1);
    ASSERT_EQ(CULT_ONE, cultsBoard.increaseCultValue(eWitches, eAir, 2));
    ASSERT_EQ(CULT_TEN, cultsBoard.getCultValue(eWitches, eAir));

    // Step to level 3 on Water cult.
    EXPECT_CALL(mockPowerUser, addPower(1)).Times(1);
    ASSERT_EQ(CULT_THREE, cultsBoard.increaseCultValue(eWitches, eWater, 3));
    ASSERT_EQ(CULT_THREE, cultsBoard.getCultValue(eWitches, eWater));

    // Step to level 5 on Water cult.
    EXPECT_CALL(mockPowerUser, addPower(2)).Times(1);
    ASSERT_EQ(CULT_TWO, cultsBoard.increaseCultValue(eWitches, eWater, 2));
    ASSERT_EQ(CULT_FIVE, cultsBoard.getCultValue(eWitches, eWater));

    // Step to level 7 on Water cult.
    EXPECT_CALL(mockPowerUser, addPower(2)).Times(1);
    ASSERT_EQ(CULT_TWO, cultsBoard.increaseCultValue(eWitches, eWater, 2));
    ASSERT_EQ(CULT_SEVEN, cultsBoard.getCultValue(eWitches, eWater));

    // Tries step to level 10 on Water cult, won't succeed.
    EXPECT_CALL(mockPowerUser, getNumberOfKeys()).Times(1).WillOnce(Return(ONE_KEY));
    ASSERT_EQ(CULT_TWO, cultsBoard.increaseCultValue(eWitches, eWater, 3));
    ASSERT_EQ(CULT_NINE, cultsBoard.getCultValue(eWitches, eWater));
}

TEST_F(CultsBoardTest, two_faction_should_not_move_to_lvl10_on_the_same_cult)
{
    MockIPowerUser cmMockPowerUser;
    CultsBoard cultsBoard;
    ASSERT_TRUE(cultsBoard.addFaction(eWitches, mockPowerUser, 0, 0, 0, 2));
    ASSERT_TRUE(cultsBoard.addFaction(eChaosMagicians, cmMockPowerUser, 2, 0, 0, 0));

    // Step to value 5 on Air with Witches
    EXPECT_CALL(mockPowerUser, addPower(CULT_THREE)).Times(1);
    ASSERT_EQ(CULT_THREE, cultsBoard.increaseCultValue(eWitches, eAir, CULT_THREE));
    ASSERT_EQ(CULT_FIVE, cultsBoard.getCultValue(eWitches, eAir));

    // Step to value 3 on Air with Chaos Magicians
    EXPECT_CALL(cmMockPowerUser, addPower(1)).Times(1);
    ASSERT_EQ(CULT_THREE, cultsBoard.increaseCultValue(eChaosMagicians, eAir, CULT_THREE));
    ASSERT_EQ(CULT_THREE, cultsBoard.getCultValue(eChaosMagicians, eAir));

    // Step to value 7 on Air with Witches
    EXPECT_CALL(mockPowerUser, addPower(CULT_TWO)).Times(1);
    ASSERT_EQ(CULT_TWO, cultsBoard.increaseCultValue(eWitches, eAir, 2));
    ASSERT_EQ(CULT_SEVEN, cultsBoard.getCultValue(eWitches, eAir));

    // Step to value 6 on Air with Chaos Magicians
    EXPECT_CALL(cmMockPowerUser, addPower(CULT_TWO)).Times(1);
    ASSERT_EQ(CULT_THREE, cultsBoard.increaseCultValue(eChaosMagicians, eAir, CULT_THREE));
    ASSERT_EQ(CULT_SIX, cultsBoard.getCultValue(eChaosMagicians, eAir));

    // Step to value 9 on Air with Witches
    ASSERT_EQ(CULT_TWO, cultsBoard.increaseCultValue(eWitches, eAir, 2));
    ASSERT_EQ(CULT_NINE, cultsBoard.getCultValue(eWitches, eAir));

    // Step to value 8 on Air with Chaos Magicians
    EXPECT_CALL(cmMockPowerUser, addPower(CULT_TWO)).Times(1);
    ASSERT_EQ(CULT_TWO, cultsBoard.increaseCultValue(eChaosMagicians, eAir, 2));
    ASSERT_EQ(CULT_EIGHT, cultsBoard.getCultValue(eChaosMagicians, eAir));

    // Try to step to value 10 with Witches and it will succeed.
    const unsigned int ONE_KEY = 1;
    EXPECT_CALL(mockPowerUser, getNumberOfKeys()).Times(1).WillOnce(Return(ONE_KEY));
    EXPECT_CALL(mockPowerUser, addPower(CULT_THREE)).Times(1);
    ASSERT_EQ(CULT_ONE, cultsBoard.increaseCultValue(eWitches, eAir, 2));
    ASSERT_EQ(CULT_TEN, cultsBoard.getCultValue(eWitches, eAir));

    // Try to step to value 10 with Chaos Magicians and it will NOT succeed.
    EXPECT_CALL(cmMockPowerUser, getNumberOfKeys()).Times(0);
    ASSERT_EQ(CULT_ONE, cultsBoard.increaseCultValue(eChaosMagicians, eAir, 2));
    ASSERT_EQ(CULT_NINE, cultsBoard.getCultValue(eChaosMagicians, eAir));
}

TEST_F(CultsBoardTest, increasing_cult_value_over_10_should_be_max_10_or_9_when_no_key)
{
    MockIPowerUser cmMockPowerUser;
    CultsBoard cultsBoard;
    ASSERT_TRUE(cultsBoard.addFaction(eWitches, mockPowerUser, 0, 0, 0, 2));
    ASSERT_TRUE(cultsBoard.addFaction(eChaosMagicians, cmMockPowerUser, 2, 0, 0, 0));

    const unsigned int ONE_KEY = 1;
    EXPECT_CALL(mockPowerUser, getNumberOfKeys()).Times(1).WillOnce(Return(ONE_KEY));
    EXPECT_CALL(mockPowerUser, addPower(CULT_EIGHT)).Times(1);
    ASSERT_EQ(CULT_TEN, cultsBoard.increaseCultValue(eWitches, eFire, 42));
    ASSERT_EQ(CULT_TEN, cultsBoard.getCultValue(eWitches, eFire));

    EXPECT_CALL(cmMockPowerUser, getNumberOfKeys()).Times(0);
    EXPECT_CALL(cmMockPowerUser, addPower(5)).Times(1);
    ASSERT_EQ(CULT_SEVEN, cultsBoard.increaseCultValue(eChaosMagicians, eFire, 42));
    ASSERT_EQ(CULT_NINE, cultsBoard.getCultValue(eChaosMagicians, eFire));
}

TEST_F(CultsBoardTest, increasing_cult_value_when_current_cult_value_already_10_should_be_no_effect)
{
    MockIPowerUser cmMockPowerUser;
    CultsBoard cultsBoard;
    ASSERT_TRUE(cultsBoard.addFaction(eWitches, mockPowerUser, 0, 0, 0, 2));
    ASSERT_TRUE(cultsBoard.addFaction(eChaosMagicians, cmMockPowerUser, 2, 0, 0, 0));

    const unsigned int ONE_KEY = 1;
    EXPECT_CALL(mockPowerUser, getNumberOfKeys()).Times(1).WillOnce(Return(ONE_KEY));
    EXPECT_CALL(mockPowerUser, addPower(CULT_EIGHT)).Times(1);
    ASSERT_EQ(CULT_TEN, cultsBoard.increaseCultValue(eWitches, eFire, 42));
    ASSERT_EQ(CULT_TEN, cultsBoard.getCultValue(eWitches, eFire));

    ASSERT_EQ(CULT_ZERO, cultsBoard.increaseCultValue(eWitches, eFire, 42));
    ASSERT_EQ(CULT_TEN, cultsBoard.getCultValue(eWitches, eFire));
}

TEST_F(CultsBoardTest, initialized_to_9_10_and_greater_than_10_it_should_be_max_10)
{
    CultsBoard cultsBoard;
    const unsigned int TWO_KEYS = 2;
    EXPECT_CALL(mockPowerUser, getNumberOfKeys()).Times(3).WillRepeatedly(Return(TWO_KEYS));
    EXPECT_CALL(mockPowerUser, addPower(::testing::_)).Times(0);

    ASSERT_TRUE(cultsBoard.addFaction(eWitches, mockPowerUser, 9, 10, 28, 42));

    ASSERT_EQ(CULT_NINE, cultsBoard.getCultValue(eWitches, eFire));
    ASSERT_EQ(CULT_TEN, cultsBoard.getCultValue(eWitches, eWater));
    ASSERT_EQ(CULT_TEN, cultsBoard.getCultValue(eWitches, eEarth));
    ASSERT_EQ(CULT_NINE, cultsBoard.getCultValue(eWitches, eAir));
}

TEST_F(CultsBoardTest, sending_priest_to_a_cult_track_should_increase_by_3_at_first_time)
{
    CultsBoard cultsBoard;
    NullPowerUser nullPowerUser;

    ASSERT_TRUE(cultsBoard.addFaction(eChaosMagicians, nullPowerUser, 2, 0, 0, 0));

    ASSERT_EQ(CULT_THREE, cultsBoard.sendPriestToMaxSteps(eChaosMagicians, eWater));
    ASSERT_EQ(CULT_THREE, cultsBoard.getCultValue(eChaosMagicians, eWater));
}

TEST_F(CultsBoardTest, sending_priest_should_increase_by_2_when_its_the_second_priest)
{
    CultsBoard cultsBoard;
    NullPowerUser nullPowerUser;

    ASSERT_TRUE(cultsBoard.addFaction(eChaosMagicians, nullPowerUser, 2, 0, 0, 0));

    ASSERT_EQ(CULT_THREE, cultsBoard.sendPriestToMaxSteps(eChaosMagicians, eWater));
    ASSERT_EQ(CULT_THREE, cultsBoard.getCultValue(eChaosMagicians, eWater));

    ASSERT_EQ(CULT_TWO, cultsBoard.sendPriestToMaxSteps(eChaosMagicians, eWater));
    ASSERT_EQ(CULT_FIVE, cultsBoard.getCultValue(eChaosMagicians, eWater));
}

TEST_F(CultsBoardTest, sending_priest_should_increasing_by_1_after_the_fourth_sent_priest)
{
    CultsBoard cultsBoard;
    NullPowerUser nullPowerUser;

    ASSERT_TRUE(cultsBoard.addFaction(eChaosMagicians, nullPowerUser, 2, 0, 0, 0));
    ASSERT_TRUE(cultsBoard.addFaction(eWitches, nullPowerUser, 0, 0, 0, 2));
    ASSERT_TRUE(cultsBoard.addFaction(eFakirs, nullPowerUser, 1, 0, 0, 1));

    ASSERT_EQ(CULT_THREE, cultsBoard.sendPriestToMaxSteps(eChaosMagicians, eEarth));
    ASSERT_EQ(CULT_THREE, cultsBoard.getCultValue(eChaosMagicians, eEarth)); 
    
    ASSERT_EQ(CULT_TWO, cultsBoard.sendPriestToMaxSteps(eWitches, eEarth));
    ASSERT_EQ(CULT_TWO, cultsBoard.getCultValue(eWitches, eEarth)); 

    ASSERT_EQ(CULT_TWO, cultsBoard.sendPriestToMaxSteps(eFakirs, eEarth));
    ASSERT_EQ(CULT_TWO, cultsBoard.getCultValue(eFakirs, eEarth)); 

    ASSERT_EQ(CULT_TWO, cultsBoard.sendPriestToMaxSteps(eChaosMagicians, eEarth));
    ASSERT_EQ(CULT_FIVE, cultsBoard.getCultValue(eChaosMagicians, eEarth)); 

    ASSERT_EQ(CULT_ONE, cultsBoard.sendPriestToMaxSteps(eWitches, eEarth));
    ASSERT_EQ(CULT_THREE, cultsBoard.getCultValue(eWitches, eEarth)); 
}

TEST_F(CultsBoardTest, sending_priest_should_not_affect_on_other_factions)
{
    CultsBoard cultsBoard;
    NullPowerUser nullPowerUser;

    ASSERT_TRUE(cultsBoard.addFaction(eChaosMagicians, nullPowerUser, 2, 0, 0, 0));
    ASSERT_TRUE(cultsBoard.addFaction(eWitches, nullPowerUser, 0, 0, 0, 2));
    ASSERT_TRUE(cultsBoard.addFaction(eFakirs, nullPowerUser, 1, 0, 0, 1));

    ASSERT_EQ(CULT_TWO, cultsBoard.getCultValue(eChaosMagicians, eFire));
    ASSERT_EQ(CULT_ZERO, cultsBoard.getCultValue(eWitches, eFire));
    ASSERT_EQ(CULT_ONE, cultsBoard.getCultValue(eFakirs, eFire));

    ASSERT_EQ(CULT_THREE, cultsBoard.sendPriestToMaxSteps(eFakirs, eFire));
    ASSERT_EQ(CULT_FOUR, cultsBoard.getCultValue(eFakirs, eFire)); 
    ASSERT_EQ(CULT_TWO, cultsBoard.getCultValue(eChaosMagicians, eFire));
    ASSERT_EQ(CULT_ZERO, cultsBoard.getCultValue(eWitches, eFire));
}

TEST_F(CultsBoardTest, stepping_over_power_lines_should_be_indicated_with_call_back)
{
    CultsBoard cultsBoard;

    ASSERT_TRUE(cultsBoard.addFaction(eChaosMagicians, mockPowerUser, 2, 0, 0, 0));

    EXPECT_CALL(mockPowerUser, addPower(CULT_THREE)).Times(1);

    ASSERT_EQ(CULT_THREE, cultsBoard.sendPriestToMaxSteps(eChaosMagicians, eFire));
    ASSERT_EQ(CULT_FIVE, cultsBoard.getCultValue(eChaosMagicians, eFire));

    EXPECT_CALL(mockPowerUser, addPower(CULT_TWO)).Times(1);

    ASSERT_EQ(CULT_TWO, cultsBoard.sendPriestToMaxSteps(eChaosMagicians, eFire));
    ASSERT_EQ(CULT_SEVEN, cultsBoard.getCultValue(eChaosMagicians, eFire));
}
