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

TEST_F(CultsBoardTest, test_add_faction)
{
    CultsBoard cultsBoard;
    EXPECT_CALL(mockPowerUser, addPower(::testing::_)).Times(0);
    EXPECT_CALL(mockPowerUser, getNumberOfKeys()).Times(0);
    ASSERT_TRUE(cultsBoard.addFaction(eChaosMagicians, mockPowerUser, 2, 0, 0, 0));
    ASSERT_EQ(2, cultsBoard.getCultValue(eChaosMagicians, eFire));
    ASSERT_EQ(0, cultsBoard.getCultValue(eChaosMagicians, eWater));
    ASSERT_EQ(0, cultsBoard.getCultValue(eChaosMagicians, eEarth));
    ASSERT_EQ(0, cultsBoard.getCultValue(eChaosMagicians, eAir));
}

TEST_F(CultsBoardTest, test_try_to_add_the_same_faction_twice)
{
    CultsBoard cultsBoard;
    ASSERT_TRUE(cultsBoard.addFaction(eChaosMagicians, mockPowerUser, 2, 0, 0, 0));
    ASSERT_EQ(2, cultsBoard.getCultValue(eChaosMagicians, eFire));
    ASSERT_EQ(0, cultsBoard.getCultValue(eChaosMagicians, eWater));
    ASSERT_EQ(0, cultsBoard.getCultValue(eChaosMagicians, eEarth));
    ASSERT_EQ(0, cultsBoard.getCultValue(eChaosMagicians, eAir));

    EXPECT_CALL(mockPowerUser, addPower(3)).Times(1);
    ASSERT_EQ(3, cultsBoard.increaseCultValue(eChaosMagicians, eFire, 3));
    EXPECT_CALL(mockPowerUser, addPower(1)).Times(1);
    ASSERT_EQ(3, cultsBoard.increaseCultValue(eChaosMagicians, eWater, 3));
    EXPECT_CALL(mockPowerUser, addPower(1)).Times(1);
    ASSERT_EQ(3, cultsBoard.increaseCultValue(eChaosMagicians, eEarth, 3));
    EXPECT_CALL(mockPowerUser, addPower(1)).Times(1);
    ASSERT_EQ(3, cultsBoard.increaseCultValue(eChaosMagicians, eAir, 3));

    ASSERT_EQ(5, cultsBoard.getCultValue(eChaosMagicians, eFire));
    ASSERT_EQ(3, cultsBoard.getCultValue(eChaosMagicians, eWater));
    ASSERT_EQ(3, cultsBoard.getCultValue(eChaosMagicians, eEarth));
    ASSERT_EQ(3, cultsBoard.getCultValue(eChaosMagicians, eAir));

    ASSERT_FALSE(cultsBoard.addFaction(eChaosMagicians, mockPowerUser, 2, 0, 0, 0));
    ASSERT_EQ(5, cultsBoard.getCultValue(eChaosMagicians, eFire));
    ASSERT_EQ(3, cultsBoard.getCultValue(eChaosMagicians, eWater));
    ASSERT_EQ(3, cultsBoard.getCultValue(eChaosMagicians, eEarth));
    ASSERT_EQ(3, cultsBoard.getCultValue(eChaosMagicians, eAir));
}

TEST_F(CultsBoardTest, test_increasing_value_before_adding_faction_is_not_possible)
{
    CultsBoard cultsBoard;
    NullPowerUser nullPowerUser;
    ASSERT_EQ(0, cultsBoard.increaseCultValue(eChaosMagicians, eWater, 2));
    ASSERT_EQ(0, cultsBoard.getCultValue(eChaosMagicians, eWater));
    ASSERT_TRUE(cultsBoard.addFaction(eChaosMagicians, nullPowerUser, 2, 0, 0, 0));
    ASSERT_EQ(2, cultsBoard.increaseCultValue(eChaosMagicians, eWater, 2));
    ASSERT_EQ(2, cultsBoard.getCultValue(eChaosMagicians, eWater));
}

TEST_F(CultsBoardTest, test_increasing_value_for_1_faction_by_2_on_one_track)
{
    CultsBoard cultsBoard;
    NullPowerUser nullPowerUser;
    ASSERT_TRUE(cultsBoard.addFaction(eFakirs, nullPowerUser, 0, 1, 0, 1));
    ASSERT_EQ(2, cultsBoard.increaseCultValue(eFakirs, eFire, 2));
    ASSERT_EQ(2, cultsBoard.getCultValue(eFakirs, eFire));
}

TEST_F(CultsBoardTest, test_increasing_value_by_2_on_one_track_for_ChaosMagicians)
{
    CultsBoard cultsBoard;
    ASSERT_TRUE(cultsBoard.addFaction(eChaosMagicians, mockPowerUser, 2, 0, 0, 0));

    EXPECT_CALL(mockPowerUser, addPower(3)).Times(1);
    ASSERT_EQ(3, cultsBoard.increaseCultValue(eChaosMagicians, eFire, 3));
    ASSERT_EQ(5, cultsBoard.getCultValue(eChaosMagicians, eFire));

    EXPECT_CALL(mockPowerUser, addPower(2)).Times(1);
    ASSERT_EQ(2, cultsBoard.increaseCultValue(eChaosMagicians, eFire, 2));
    ASSERT_EQ(7, cultsBoard.getCultValue(eChaosMagicians, eFire));

    ASSERT_EQ(2, cultsBoard.increaseCultValue(eChaosMagicians, eFire, 2));
    ASSERT_EQ(9, cultsBoard.getCultValue(eChaosMagicians, eFire));

    EXPECT_CALL(mockPowerUser, addPower(3)).Times(1);
    EXPECT_CALL(mockPowerUser, getNumberOfKeys()).Times(1).WillOnce(Return(1));
    ASSERT_EQ(1, cultsBoard.increaseCultValue(eChaosMagicians, eFire, 1));
    ASSERT_EQ(10, cultsBoard.getCultValue(eChaosMagicians, eFire));
}

TEST_F(CultsBoardTest, test_increasing_value_for_1_faction_by_1_on_one_track)
{
    CultsBoard cultsBoard;
    NullPowerUser nullPowerUser;
    ASSERT_TRUE(cultsBoard.addFaction(eFakirs, nullPowerUser, 0, 1, 0, 1));
    ASSERT_EQ(1, cultsBoard.increaseCultValue(eFakirs, eFire, 1));
    ASSERT_EQ(1, cultsBoard.getCultValue(eFakirs, eFire));
}

TEST_F(CultsBoardTest, test_increasing_value_for_1_faction_by_3_on_one_track)
{
    CultsBoard cultsBoard;
    NullPowerUser nullPowerUser;
    ASSERT_TRUE(cultsBoard.addFaction(eFakirs, nullPowerUser, 0, 1, 0, 1));

    ASSERT_EQ(3, cultsBoard.increaseCultValue(eFakirs, eFire, 3));
    ASSERT_EQ(3, cultsBoard.getCultValue(eFakirs, eFire));
}

TEST_F(CultsBoardTest, test_increasing_value_for_1_faction_by_1_then_2_on_one_track)
{
    CultsBoard cultsBoard;
    NullPowerUser nullPowerUser;
    ASSERT_TRUE(cultsBoard.addFaction(eFakirs, nullPowerUser, 0, 1, 0, 1));

    ASSERT_EQ(1, cultsBoard.increaseCultValue(eFakirs, eFire, 1));
    ASSERT_EQ(1, cultsBoard.getCultValue(eFakirs, eFire));

    ASSERT_EQ(2, cultsBoard.increaseCultValue(eFakirs, eFire, 2));
    ASSERT_EQ(3, cultsBoard.getCultValue(eFakirs, eFire));
}

TEST_F(CultsBoardTest, test_increasing_value_for_1_faction_by_2_then_1_on_one_track)
{
    CultsBoard cultsBoard;
    NullPowerUser nullPowerUser;
    ASSERT_TRUE(cultsBoard.addFaction(eFakirs, nullPowerUser, 0, 1, 0, 1));

    ASSERT_EQ(2, cultsBoard.increaseCultValue(eFakirs, eFire, 2));
    ASSERT_EQ(2, cultsBoard.getCultValue(eFakirs, eFire));

    ASSERT_EQ(1, cultsBoard.increaseCultValue(eFakirs, eFire, 1));
    ASSERT_EQ(3, cultsBoard.getCultValue(eFakirs, eFire));
}

TEST_F(CultsBoardTest, test_increasing_value_for_1_faction_by_2_then_1_on_two_tracks)
{
    CultsBoard cultsBoard;
    NullPowerUser nullPowerUser;
    ASSERT_TRUE(cultsBoard.addFaction(eFakirs, nullPowerUser, 0, 1, 0, 1));

    ASSERT_EQ(2, cultsBoard.increaseCultValue(eFakirs, eFire, 2));
    ASSERT_EQ(2, cultsBoard.getCultValue(eFakirs, eFire));
    ASSERT_EQ(1, cultsBoard.getCultValue(eFakirs, eWater));

    ASSERT_EQ(1, cultsBoard.increaseCultValue(eFakirs, eWater, 1));
    ASSERT_EQ(2, cultsBoard.getCultValue(eFakirs, eWater));
    ASSERT_EQ(2, cultsBoard.getCultValue(eFakirs, eFire));

    ASSERT_EQ(1, cultsBoard.increaseCultValue(eFakirs, eFire, 1));
    ASSERT_EQ(3, cultsBoard.getCultValue(eFakirs, eFire));
    ASSERT_EQ(2, cultsBoard.getCultValue(eFakirs, eWater));

    ASSERT_EQ(2, cultsBoard.increaseCultValue(eFakirs, eWater, 2));
    ASSERT_EQ(3, cultsBoard.getCultValue(eFakirs, eFire));
    ASSERT_EQ(4, cultsBoard.getCultValue(eFakirs, eWater));
}

TEST_F(CultsBoardTest, test_increasing_value_for_2_factions_by_2_on_one_track)
{
    CultsBoard cultsBoard;
    NullPowerUser nullPowerUser;
    ASSERT_TRUE(cultsBoard.addFaction(eFakirs, nullPowerUser, 0, 1, 0, 1));
    ASSERT_TRUE(cultsBoard.addFaction(eChaosMagicians, nullPowerUser, 2, 0, 0, 0));

    ASSERT_EQ(2, cultsBoard.increaseCultValue(eFakirs, eFire, 2));
    ASSERT_EQ(2, cultsBoard.getCultValue(eFakirs, eFire));
    ASSERT_EQ(2, cultsBoard.getCultValue(eChaosMagicians, eFire));

    ASSERT_EQ(2, cultsBoard.increaseCultValue(eChaosMagicians, eFire, 2));
    ASSERT_EQ(2, cultsBoard.getCultValue(eFakirs, eFire));
    ASSERT_EQ(4, cultsBoard.getCultValue(eChaosMagicians, eFire));
}

TEST_F(CultsBoardTest, test_increasing_value_for_2_factions_by_2_then_1_on_two_tracks)
{
    CultsBoard cultsBoard;
    NullPowerUser nullPowerUser;
    ASSERT_TRUE(cultsBoard.addFaction(eFakirs, nullPowerUser, 0, 0, 0, 0));
    ASSERT_TRUE(cultsBoard.addFaction(eChaosMagicians, nullPowerUser, 0, 0, 0, 0));

    ASSERT_EQ(2, cultsBoard.increaseCultValue(eFakirs, eFire, 2));
    ASSERT_EQ(2, cultsBoard.getCultValue(eFakirs, eFire));
    ASSERT_EQ(0, cultsBoard.getCultValue(eFakirs, eWater));
    ASSERT_EQ(0, cultsBoard.getCultValue(eChaosMagicians, eFire));
    ASSERT_EQ(0, cultsBoard.getCultValue(eChaosMagicians, eWater));

    ASSERT_EQ(2, cultsBoard.increaseCultValue(eChaosMagicians, eWater, 2));
    ASSERT_EQ(2, cultsBoard.getCultValue(eFakirs, eFire));
    ASSERT_EQ(0, cultsBoard.getCultValue(eFakirs, eWater));
    ASSERT_EQ(0, cultsBoard.getCultValue(eChaosMagicians, eFire));
    ASSERT_EQ(2, cultsBoard.getCultValue(eChaosMagicians, eWater));

    ASSERT_EQ(1, cultsBoard.increaseCultValue(eFakirs, eWater, 1));
    ASSERT_EQ(2, cultsBoard.getCultValue(eFakirs, eFire));
    ASSERT_EQ(1, cultsBoard.getCultValue(eFakirs, eWater));
    ASSERT_EQ(0, cultsBoard.getCultValue(eChaosMagicians, eFire));
    ASSERT_EQ(2, cultsBoard.getCultValue(eChaosMagicians, eWater));

    ASSERT_EQ(1, cultsBoard.increaseCultValue(eChaosMagicians, eFire, 1));
    ASSERT_EQ(2, cultsBoard.getCultValue(eFakirs, eFire));
    ASSERT_EQ(1, cultsBoard.getCultValue(eFakirs, eWater));
    ASSERT_EQ(1, cultsBoard.getCultValue(eChaosMagicians, eFire));
    ASSERT_EQ(2, cultsBoard.getCultValue(eChaosMagicians, eWater));

    ASSERT_EQ(1, cultsBoard.increaseCultValue(eFakirs, eFire, 1));
    ASSERT_EQ(3, cultsBoard.getCultValue(eFakirs, eFire));
    ASSERT_EQ(1, cultsBoard.getCultValue(eFakirs, eWater));
    ASSERT_EQ(1, cultsBoard.getCultValue(eChaosMagicians, eFire));
    ASSERT_EQ(2, cultsBoard.getCultValue(eChaosMagicians, eWater));

    ASSERT_EQ(1, cultsBoard.increaseCultValue(eChaosMagicians, eWater, 1));
    ASSERT_EQ(3, cultsBoard.getCultValue(eFakirs, eFire));
    ASSERT_EQ(1, cultsBoard.getCultValue(eFakirs, eWater));
    ASSERT_EQ(1, cultsBoard.getCultValue(eChaosMagicians, eFire));
    ASSERT_EQ(3, cultsBoard.getCultValue(eChaosMagicians, eWater));

    ASSERT_EQ(2, cultsBoard.increaseCultValue(eFakirs, eWater, 2));
    ASSERT_EQ(3, cultsBoard.getCultValue(eFakirs, eFire));
    ASSERT_EQ(3, cultsBoard.getCultValue(eFakirs, eWater));
    ASSERT_EQ(1, cultsBoard.getCultValue(eChaosMagicians, eFire));
    ASSERT_EQ(3, cultsBoard.getCultValue(eChaosMagicians, eWater));

    ASSERT_EQ(2, cultsBoard.increaseCultValue(eChaosMagicians, eFire, 2));
    ASSERT_EQ(3, cultsBoard.getCultValue(eFakirs, eFire));
    ASSERT_EQ(3, cultsBoard.getCultValue(eFakirs, eWater));
    ASSERT_EQ(3, cultsBoard.getCultValue(eChaosMagicians, eFire));
    ASSERT_EQ(3, cultsBoard.getCultValue(eChaosMagicians, eWater));
}

TEST_F(CultsBoardTest, test_increasing_value_for_3_factions_by_2_on_one_track)
{
    CultsBoard cultsBoard;
    NullPowerUser nullPowerUser;
    ASSERT_TRUE(cultsBoard.addFaction(eFakirs, nullPowerUser, 0, 0, 0, 0));
    ASSERT_TRUE(cultsBoard.addFaction(eChaosMagicians, nullPowerUser, 0, 0, 0, 0));
    ASSERT_TRUE(cultsBoard.addFaction(eWitches, nullPowerUser, 0, 0, 0, 0));

    ASSERT_EQ(2, cultsBoard.increaseCultValue(eFakirs, eFire, 2));
    ASSERT_EQ(2, cultsBoard.getCultValue(eFakirs, eFire));
    ASSERT_EQ(0, cultsBoard.getCultValue(eChaosMagicians, eFire));
    ASSERT_EQ(0, cultsBoard.getCultValue(eWitches, eFire));

    ASSERT_EQ(2, cultsBoard.increaseCultValue(eChaosMagicians, eFire, 2));
    ASSERT_EQ(2, cultsBoard.getCultValue(eFakirs, eFire));
    ASSERT_EQ(2, cultsBoard.getCultValue(eChaosMagicians, eFire));
    ASSERT_EQ(0, cultsBoard.getCultValue(eWitches, eFire));

    ASSERT_EQ(2, cultsBoard.increaseCultValue(eWitches, eFire, 2));
    ASSERT_EQ(2, cultsBoard.getCultValue(eFakirs, eFire));
    ASSERT_EQ(2, cultsBoard.getCultValue(eChaosMagicians, eFire));
    ASSERT_EQ(2, cultsBoard.getCultValue(eWitches, eFire));
}

TEST_F(CultsBoardTest, test_dont_let_step_to_level_10_because_no_keys_has_the_faction)
{
    CultsBoard cultsBoard;
    ASSERT_TRUE(cultsBoard.addFaction(eWitches, mockPowerUser, 0, 0, 0, 2));

    // Step to value 5
    EXPECT_CALL(mockPowerUser, addPower(3)).Times(1);
    ASSERT_EQ(3, cultsBoard.increaseCultValue(eWitches, eAir, 3));
    ASSERT_EQ(5, cultsBoard.getCultValue(eWitches, eAir));

    // Step to value 7
    EXPECT_CALL(mockPowerUser, addPower(2)).Times(1);
    ASSERT_EQ(2, cultsBoard.increaseCultValue(eWitches, eAir, 2));
    ASSERT_EQ(7, cultsBoard.getCultValue(eWitches, eAir));

    // Step to value 9
    ASSERT_EQ(2, cultsBoard.increaseCultValue(eWitches, eAir, 2));
    ASSERT_EQ(9, cultsBoard.getCultValue(eWitches, eAir));

    // Try to step to value 10 but no success with it.
    const unsigned int NO_KEYS = 0;
    EXPECT_CALL(mockPowerUser, getNumberOfKeys()).Times(1).WillOnce(Return(NO_KEYS));
    ASSERT_EQ(0, cultsBoard.increaseCultValue(eWitches, eAir, 1));
    ASSERT_EQ(9, cultsBoard.getCultValue(eWitches, eAir));
}

TEST_F(CultsBoardTest, test_try_to_step_over_level_10_but_let_only_level_10_there_is_a_key)
{
    CultsBoard cultsBoard;
    ASSERT_TRUE(cultsBoard.addFaction(eWitches, mockPowerUser, 0, 0, 0, 2));

    // Step to value 5
    EXPECT_CALL(mockPowerUser, addPower(3)).Times(1);
    ASSERT_EQ(3, cultsBoard.increaseCultValue(eWitches, eAir, 3));
    ASSERT_EQ(5, cultsBoard.getCultValue(eWitches, eAir));

    // Step to value 7
    EXPECT_CALL(mockPowerUser, addPower(2)).Times(1);
    ASSERT_EQ(2, cultsBoard.increaseCultValue(eWitches, eAir, 2));
    ASSERT_EQ(7, cultsBoard.getCultValue(eWitches, eAir));

    // Step to value 9
    ASSERT_EQ(2, cultsBoard.increaseCultValue(eWitches, eAir, 2));
    ASSERT_EQ(9, cultsBoard.getCultValue(eWitches, eAir));

    // Try to step to value 10 and it will succeed.
    const unsigned int ONE_KEY = 1;
    EXPECT_CALL(mockPowerUser, getNumberOfKeys()).Times(1).WillOnce(Return(ONE_KEY));
    EXPECT_CALL(mockPowerUser, addPower(3)).Times(1);
    ASSERT_EQ(1, cultsBoard.increaseCultValue(eWitches, eAir, 2));
    ASSERT_EQ(10, cultsBoard.getCultValue(eWitches, eAir));
}

TEST_F(CultsBoardTest, test_one_key_and_tries_to_step_lvl_10_on_more_cults)
{
    CultsBoard cultsBoard;
    ASSERT_TRUE(cultsBoard.addFaction(eWitches, mockPowerUser, 0, 0, 0, 2));

    // Step to value 5 on Air
    EXPECT_CALL(mockPowerUser, addPower(3)).Times(1);
    ASSERT_EQ(3, cultsBoard.increaseCultValue(eWitches, eAir, 3));
    ASSERT_EQ(5, cultsBoard.getCultValue(eWitches, eAir));

    // Step to value 7 on Air
    EXPECT_CALL(mockPowerUser, addPower(2)).Times(1);
    ASSERT_EQ(2, cultsBoard.increaseCultValue(eWitches, eAir, 2));
    ASSERT_EQ(7, cultsBoard.getCultValue(eWitches, eAir));

    // Step to value 9 on Air
    ASSERT_EQ(2, cultsBoard.increaseCultValue(eWitches, eAir, 2));
    ASSERT_EQ(9, cultsBoard.getCultValue(eWitches, eAir));

    // Try to step to value 10 and it will succeed.
    const unsigned int ONE_KEY = 1;
    EXPECT_CALL(mockPowerUser, getNumberOfKeys()).Times(1).WillOnce(Return(ONE_KEY));
    EXPECT_CALL(mockPowerUser, addPower(3)).Times(1);
    ASSERT_EQ(1, cultsBoard.increaseCultValue(eWitches, eAir, 2));
    ASSERT_EQ(10, cultsBoard.getCultValue(eWitches, eAir));

    // Step to level 3 on Water cult.
    EXPECT_CALL(mockPowerUser, addPower(1)).Times(1);
    ASSERT_EQ(3, cultsBoard.increaseCultValue(eWitches, eWater, 3));
    ASSERT_EQ(3, cultsBoard.getCultValue(eWitches, eWater));

    // Step to level 5 on Water cult.
    EXPECT_CALL(mockPowerUser, addPower(2)).Times(1);
    ASSERT_EQ(2, cultsBoard.increaseCultValue(eWitches, eWater, 2));
    ASSERT_EQ(5, cultsBoard.getCultValue(eWitches, eWater));

    // Step to level 7 on Water cult.
    EXPECT_CALL(mockPowerUser, addPower(2)).Times(1);
    ASSERT_EQ(2, cultsBoard.increaseCultValue(eWitches, eWater, 2));
    ASSERT_EQ(7, cultsBoard.getCultValue(eWitches, eWater));

    // Tries step to level 10 on Water cult, won't succeed.
    EXPECT_CALL(mockPowerUser, getNumberOfKeys()).Times(1).WillOnce(Return(ONE_KEY));
    ASSERT_EQ(2, cultsBoard.increaseCultValue(eWitches, eWater, 3));
    ASSERT_EQ(9, cultsBoard.getCultValue(eWitches, eWater));
}

TEST_F(CultsBoardTest, test_two_faction_can_not_move_to_lvl10_on_the_same_cult)
{
    MockIPowerUser cmMockPowerUser;
    CultsBoard cultsBoard;
    ASSERT_TRUE(cultsBoard.addFaction(eWitches, mockPowerUser, 0, 0, 0, 2));
    ASSERT_TRUE(cultsBoard.addFaction(eChaosMagicians, cmMockPowerUser, 2, 0, 0, 0));

    // Step to value 5 on Air with Witches
    EXPECT_CALL(mockPowerUser, addPower(3)).Times(1);
    ASSERT_EQ(3, cultsBoard.increaseCultValue(eWitches, eAir, 3));
    ASSERT_EQ(5, cultsBoard.getCultValue(eWitches, eAir));

    // Step to value 3 on Air with Chaos Magicians
    EXPECT_CALL(cmMockPowerUser, addPower(1)).Times(1);
    ASSERT_EQ(3, cultsBoard.increaseCultValue(eChaosMagicians, eAir, 3));
    ASSERT_EQ(3, cultsBoard.getCultValue(eChaosMagicians, eAir));

    // Step to value 7 on Air with Witches
    EXPECT_CALL(mockPowerUser, addPower(2)).Times(1);
    ASSERT_EQ(2, cultsBoard.increaseCultValue(eWitches, eAir, 2));
    ASSERT_EQ(7, cultsBoard.getCultValue(eWitches, eAir));

    // Step to value 6 on Air with Chaos Magicians
    EXPECT_CALL(cmMockPowerUser, addPower(2)).Times(1);
    ASSERT_EQ(3, cultsBoard.increaseCultValue(eChaosMagicians, eAir, 3));
    ASSERT_EQ(6, cultsBoard.getCultValue(eChaosMagicians, eAir));

    // Step to value 9 on Air with Witches
    ASSERT_EQ(2, cultsBoard.increaseCultValue(eWitches, eAir, 2));
    ASSERT_EQ(9, cultsBoard.getCultValue(eWitches, eAir));

    // Step to value 8 on Air with Chaos Magicians
    EXPECT_CALL(cmMockPowerUser, addPower(2)).Times(1);
    ASSERT_EQ(2, cultsBoard.increaseCultValue(eChaosMagicians, eAir, 2));
    ASSERT_EQ(8, cultsBoard.getCultValue(eChaosMagicians, eAir));

    // Try to step to value 10 with Witches and it will succeed.
    const unsigned int ONE_KEY = 1;
    EXPECT_CALL(mockPowerUser, getNumberOfKeys()).Times(1).WillOnce(Return(ONE_KEY));
    EXPECT_CALL(mockPowerUser, addPower(3)).Times(1);
    ASSERT_EQ(1, cultsBoard.increaseCultValue(eWitches, eAir, 2));
    ASSERT_EQ(10, cultsBoard.getCultValue(eWitches, eAir));

    // Try to step to value 10 with Chaos Magicians and it will NOT succeed.
    EXPECT_CALL(cmMockPowerUser, getNumberOfKeys()).Times(0);
    ASSERT_EQ(1, cultsBoard.increaseCultValue(eChaosMagicians, eAir, 2));
    ASSERT_EQ(9, cultsBoard.getCultValue(eChaosMagicians, eAir));
}

TEST_F(CultsBoardTest, test_increasing_cult_value_by_more_than_10)
{
    MockIPowerUser cmMockPowerUser;
    CultsBoard cultsBoard;
    ASSERT_TRUE(cultsBoard.addFaction(eWitches, mockPowerUser, 0, 0, 0, 2));
    ASSERT_TRUE(cultsBoard.addFaction(eChaosMagicians, cmMockPowerUser, 2, 0, 0, 0));

    const unsigned int ONE_KEY = 1;
    EXPECT_CALL(mockPowerUser, getNumberOfKeys()).Times(1).WillOnce(Return(ONE_KEY));
    EXPECT_CALL(mockPowerUser, addPower(8)).Times(1);
    ASSERT_EQ(10, cultsBoard.increaseCultValue(eWitches, eFire, 42));
    ASSERT_EQ(10, cultsBoard.getCultValue(eWitches, eFire));

    EXPECT_CALL(cmMockPowerUser, getNumberOfKeys()).Times(0);
    EXPECT_CALL(cmMockPowerUser, addPower(5)).Times(1);
    ASSERT_EQ(7, cultsBoard.increaseCultValue(eChaosMagicians, eFire, 42));
    ASSERT_EQ(9, cultsBoard.getCultValue(eChaosMagicians, eFire));
}

TEST_F(CultsBoardTest, test_increasing_cult_value_when_current_cult_value_already_10)
{
    MockIPowerUser cmMockPowerUser;
    CultsBoard cultsBoard;
    ASSERT_TRUE(cultsBoard.addFaction(eWitches, mockPowerUser, 0, 0, 0, 2));
    ASSERT_TRUE(cultsBoard.addFaction(eChaosMagicians, cmMockPowerUser, 2, 0, 0, 0));

    const unsigned int ONE_KEY = 1;
    EXPECT_CALL(mockPowerUser, getNumberOfKeys()).Times(1).WillOnce(Return(ONE_KEY));
    EXPECT_CALL(mockPowerUser, addPower(8)).Times(1);
    ASSERT_EQ(10, cultsBoard.increaseCultValue(eWitches, eFire, 42));
    ASSERT_EQ(10, cultsBoard.getCultValue(eWitches, eFire));

    ASSERT_EQ(0, cultsBoard.increaseCultValue(eWitches, eFire, 42));
    ASSERT_EQ(10, cultsBoard.getCultValue(eWitches, eFire));
}

TEST_F(CultsBoardTest, test_initialized_to_9_10_and_greater_than_10_it_should_be_max_10)
{
    CultsBoard cultsBoard;
    const unsigned int TWO_KEYS = 2;
    EXPECT_CALL(mockPowerUser, getNumberOfKeys()).Times(3).WillRepeatedly(Return(TWO_KEYS));
    EXPECT_CALL(mockPowerUser, addPower(::testing::_)).Times(0);

    ASSERT_TRUE(cultsBoard.addFaction(eWitches, mockPowerUser, 9, 10, 28, 42));

    ASSERT_EQ(9, cultsBoard.getCultValue(eWitches, eFire));
    ASSERT_EQ(10, cultsBoard.getCultValue(eWitches, eWater));
    ASSERT_EQ(10, cultsBoard.getCultValue(eWitches, eEarth));
    ASSERT_EQ(9, cultsBoard.getCultValue(eWitches, eAir));
}
