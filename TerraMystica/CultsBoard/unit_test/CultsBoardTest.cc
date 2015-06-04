#include "CultsBoard.hh"
#include "Factions.hh"
#include "gtest/gtest.h"
#include "MockIPowerUser.hh"
#include <iostream>

using namespace std;

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
    ASSERT_TRUE(cultsBoard.addFaction(eChaosMagicians, &mockPowerUser, 2, 0, 0, 0));
    ASSERT_EQ(2, cultsBoard.getCultValue(eChaosMagicians, eFire));
    ASSERT_EQ(0, cultsBoard.getCultValue(eChaosMagicians, eWater));
    ASSERT_EQ(0, cultsBoard.getCultValue(eChaosMagicians, eEarth));
    ASSERT_EQ(0, cultsBoard.getCultValue(eChaosMagicians, eAir));
}

TEST_F(CultsBoardTest, test_increasing_value_before_adding_faction_is_not_possible)
{
    CultsBoard cultsBoard;
    ASSERT_EQ(0, cultsBoard.increaseCultValue(eChaosMagicians, eWater, 2));
    ASSERT_EQ(0, cultsBoard.getCultValue(eChaosMagicians, eWater));
    ASSERT_TRUE(cultsBoard.addFaction(eChaosMagicians, 0, 2, 0, 0, 0));
    ASSERT_EQ(2, cultsBoard.increaseCultValue(eChaosMagicians, eWater, 2));
    ASSERT_EQ(2, cultsBoard.getCultValue(eChaosMagicians, eWater));
}

TEST_F(CultsBoardTest, test_increasing_value_for_1_faction_by_2_on_one_track)
{
    CultsBoard cultsBoard;
    ASSERT_TRUE(cultsBoard.addFaction(eFakirs, 0, 0, 1, 0, 1));
    ASSERT_EQ(2, cultsBoard.increaseCultValue(eFakirs, eFire, 2));
    ASSERT_EQ(2, cultsBoard.getCultValue(eFakirs, eFire));
}

TEST_F(CultsBoardTest, test_increasing_value_by_2_on_one_track_for_ChaosMagicians)
{
    CultsBoard cultsBoard;
    ASSERT_TRUE(cultsBoard.addFaction(eChaosMagicians, &mockPowerUser, 2, 0, 0, 0));

    EXPECT_CALL(mockPowerUser, addPower(3)).Times(1);
    ASSERT_EQ(3, cultsBoard.increaseCultValue(eChaosMagicians, eFire, 3));
    ASSERT_EQ(5, cultsBoard.getCultValue(eChaosMagicians, eFire));

    EXPECT_CALL(mockPowerUser, addPower(2)).Times(1);
    ASSERT_EQ(2, cultsBoard.increaseCultValue(eChaosMagicians, eFire, 2));
    ASSERT_EQ(7, cultsBoard.getCultValue(eChaosMagicians, eFire));

    ASSERT_EQ(2, cultsBoard.increaseCultValue(eChaosMagicians, eFire, 2));
    ASSERT_EQ(9, cultsBoard.getCultValue(eChaosMagicians, eFire));

    EXPECT_CALL(mockPowerUser, addPower(3)).Times(1);
    ASSERT_EQ(1, cultsBoard.increaseCultValue(eChaosMagicians, eFire, 1));
    ASSERT_EQ(10, cultsBoard.getCultValue(eChaosMagicians, eFire));
}

TEST_F(CultsBoardTest, test_increasing_value_for_1_faction_by_1_on_one_track)
{
    CultsBoard cultsBoard;
    ASSERT_TRUE(cultsBoard.addFaction(eFakirs, 0, 0, 1, 0, 1));
    ASSERT_EQ(1, cultsBoard.increaseCultValue(eFakirs, eFire, 1));
    ASSERT_EQ(1, cultsBoard.getCultValue(eFakirs, eFire));
}

TEST_F(CultsBoardTest, test_increasing_value_for_1_faction_by_3_on_one_track)
{
    CultsBoard cultsBoard;
    ASSERT_TRUE(cultsBoard.addFaction(eFakirs, 0, 0, 1, 0, 1));

    ASSERT_EQ(3, cultsBoard.increaseCultValue(eFakirs, eFire, 3));
    ASSERT_EQ(3, cultsBoard.getCultValue(eFakirs, eFire));
}

TEST_F(CultsBoardTest, test_increasing_value_for_1_faction_by_1_then_2_on_one_track)
{
    CultsBoard cultsBoard;
    ASSERT_TRUE(cultsBoard.addFaction(eFakirs, 0, 0, 1, 0, 1));

    ASSERT_EQ(1, cultsBoard.increaseCultValue(eFakirs, eFire, 1));
    ASSERT_EQ(1, cultsBoard.getCultValue(eFakirs, eFire));

    ASSERT_EQ(2, cultsBoard.increaseCultValue(eFakirs, eFire, 2));
    ASSERT_EQ(3, cultsBoard.getCultValue(eFakirs, eFire));
}

TEST_F(CultsBoardTest, test_increasing_value_for_1_faction_by_2_then_1_on_one_track)
{
    CultsBoard cultsBoard;
    ASSERT_TRUE(cultsBoard.addFaction(eFakirs, 0, 0, 1, 0, 1));

    ASSERT_EQ(2, cultsBoard.increaseCultValue(eFakirs, eFire, 2));
    ASSERT_EQ(2, cultsBoard.getCultValue(eFakirs, eFire));

    ASSERT_EQ(1, cultsBoard.increaseCultValue(eFakirs, eFire, 1));
    ASSERT_EQ(3, cultsBoard.getCultValue(eFakirs, eFire));
}

TEST_F(CultsBoardTest, test_increasing_value_for_1_faction_by_2_then_1_on_two_tracks)
{
    CultsBoard cultsBoard;
    ASSERT_TRUE(cultsBoard.addFaction(eFakirs, 0, 0, 1, 0, 1));

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
    ASSERT_TRUE(cultsBoard.addFaction(eFakirs, 0, 0, 1, 0, 1));
    ASSERT_TRUE(cultsBoard.addFaction(eChaosMagicians, 0, 2, 0, 0, 0));

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
    ASSERT_TRUE(cultsBoard.addFaction(eFakirs, 0, 0, 0, 0, 0));
    ASSERT_TRUE(cultsBoard.addFaction(eChaosMagicians, 0, 0, 0, 0, 0));

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
    ASSERT_TRUE(cultsBoard.addFaction(eFakirs, 0, 0, 0, 0, 0));
    ASSERT_TRUE(cultsBoard.addFaction(eChaosMagicians, 0, 0, 0, 0, 0));
    ASSERT_TRUE(cultsBoard.addFaction(eWitches, 0, 0, 0, 0, 0));

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


int main(int argc, char* argv[])
{
    ::testing::InitGoogleMock(&argc, argv);
    return RUN_ALL_TESTS();
}
