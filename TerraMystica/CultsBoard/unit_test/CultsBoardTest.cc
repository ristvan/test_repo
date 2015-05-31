#include "CultsBoard.hh"
#include "Factions.hh"
#include "gtest/gtest.h"
#include <iostream>

using namespace std;

class CultsBoardTest : public ::testing::Test
{
protected:
    virtual void SetUp() { }
    virtual void TearDown() { }
};

TEST_F(CultsBoardTest, test_increasing_value_for_1_faction_by_2_on_one_track)
{
    CultsBoard cultsBoard;
    ASSERT_EQ(2, cultsBoard.increaseCultValue(eFakirs, eFire, 2));
    ASSERT_EQ(2, cultsBoard.getCultValue(eFakirs, eFire));
}

TEST_F(CultsBoardTest, test_increasing_value_for_1_faction_by_1_on_one_track)
{
    CultsBoard cultsBoard;
    ASSERT_EQ(1, cultsBoard.increaseCultValue(eFakirs, eFire, 1));
    ASSERT_EQ(1, cultsBoard.getCultValue(eFakirs, eFire));
}

TEST_F(CultsBoardTest, test_increasing_value_for_1_faction_by_3_on_one_track)
{
    CultsBoard cultsBoard;
    ASSERT_EQ(3, cultsBoard.increaseCultValue(eFakirs, eFire, 3));
    ASSERT_EQ(3, cultsBoard.getCultValue(eFakirs, eFire));
}

TEST_F(CultsBoardTest, test_increasing_value_for_1_faction_by_1_then_2_on_one_track)
{
    CultsBoard cultsBoard;
    ASSERT_EQ(1, cultsBoard.increaseCultValue(eFakirs, eFire, 1));
    ASSERT_EQ(1, cultsBoard.getCultValue(eFakirs, eFire));

    ASSERT_EQ(2, cultsBoard.increaseCultValue(eFakirs, eFire, 2));
    ASSERT_EQ(3, cultsBoard.getCultValue(eFakirs, eFire));
}

TEST_F(CultsBoardTest, test_increasing_value_for_1_faction_by_2_then_1_on_one_track)
{
    CultsBoard cultsBoard;
    ASSERT_EQ(2, cultsBoard.increaseCultValue(eFakirs, eFire, 2));
    ASSERT_EQ(2, cultsBoard.getCultValue(eFakirs, eFire));

    ASSERT_EQ(1, cultsBoard.increaseCultValue(eFakirs, eFire, 1));
    ASSERT_EQ(3, cultsBoard.getCultValue(eFakirs, eFire));
}

TEST_F(CultsBoardTest, test_increasing_value_for_1_faction_by_2_then_1_on_two_tracks)
{
    CultsBoard cultsBoard;
    // TODO: without this exception is raising
    ASSERT_EQ(0, cultsBoard.increaseCultValue(eFakirs, eWater, 0));

    ASSERT_EQ(2, cultsBoard.increaseCultValue(eFakirs, eFire, 2));
    ASSERT_EQ(2, cultsBoard.getCultValue(eFakirs, eFire));
    ASSERT_EQ(0, cultsBoard.getCultValue(eFakirs, eWater));

    ASSERT_EQ(1, cultsBoard.increaseCultValue(eFakirs, eWater, 1));
    ASSERT_EQ(1, cultsBoard.getCultValue(eFakirs, eWater));
    ASSERT_EQ(2, cultsBoard.getCultValue(eFakirs, eFire));

    ASSERT_EQ(1, cultsBoard.increaseCultValue(eFakirs, eFire, 1));
    ASSERT_EQ(3, cultsBoard.getCultValue(eFakirs, eFire));
    ASSERT_EQ(1, cultsBoard.getCultValue(eFakirs, eWater));

    ASSERT_EQ(2, cultsBoard.increaseCultValue(eFakirs, eWater, 2));
    ASSERT_EQ(3, cultsBoard.getCultValue(eFakirs, eFire));
    ASSERT_EQ(3, cultsBoard.getCultValue(eFakirs, eWater));
}

TEST_F(CultsBoardTest, test_increasing_value_for_2_factions_by_2_on_one_track)
{
    CultsBoard cultsBoard;
    // TODO: without this exception is raising
    ASSERT_EQ(0, cultsBoard.increaseCultValue(eChaosMagicians, eFire, 0));

    ASSERT_EQ(2, cultsBoard.increaseCultValue(eFakirs, eFire, 2));
    ASSERT_EQ(2, cultsBoard.getCultValue(eFakirs, eFire));
    ASSERT_EQ(0, cultsBoard.getCultValue(eChaosMagicians, eFire));

    ASSERT_EQ(2, cultsBoard.increaseCultValue(eChaosMagicians, eFire, 2));
    ASSERT_EQ(2, cultsBoard.getCultValue(eFakirs, eFire));
    ASSERT_EQ(2, cultsBoard.getCultValue(eChaosMagicians, eFire));
}

TEST_F(CultsBoardTest, test_increasing_value_for_2_factions_by_2_then_1_on_two_tracks)
{
    CultsBoard cultsBoard;
    // TODO: without this, exception is raising
    ASSERT_EQ(0, cultsBoard.increaseCultValue(eChaosMagicians, eFire, 0));
    ASSERT_EQ(0, cultsBoard.increaseCultValue(eChaosMagicians, eWater, 0));
    ASSERT_EQ(0, cultsBoard.increaseCultValue(eFakirs, eWater, 0));

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
    // TODO: without this, exception is raising
    ASSERT_EQ(0, cultsBoard.increaseCultValue(eChaosMagicians, eFire, 0));
    ASSERT_EQ(0, cultsBoard.increaseCultValue(eWitches, eFire, 0));

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
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
