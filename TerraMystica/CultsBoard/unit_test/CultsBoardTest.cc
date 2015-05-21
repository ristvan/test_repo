#include "CultsBoard.hh"
#include "gtest/gtest.h"
#include <iostream>

using namespace std;

class CultsBoardTest : public ::testing::Test
{
protected:
    virtual void SetUp() { }
    virtual void TearDown() { }
};

TEST_F(CultsBoardTest, test_increasing_value_by_2_on_one_track)
{
    CultsBoard cultsBoard;
    ASSERT_EQ(2, cultsBoard.increaseCultValue(eFire, 2));
    ASSERT_EQ(2, cultsBoard.getCultValue(eFire));
}

TEST_F(CultsBoardTest, test_increasing_value_by_1_on_one_track)
{
    CultsBoard cultsBoard;
    ASSERT_EQ(1, cultsBoard.increaseCultValue(eFire, 1));
    ASSERT_EQ(1, cultsBoard.getCultValue(eFire));
}

TEST_F(CultsBoardTest, test_increasing_value_by_3_on_one_track)
{
    CultsBoard cultsBoard;
    ASSERT_EQ(3, cultsBoard.increaseCultValue(eFire, 3));
    ASSERT_EQ(3, cultsBoard.getCultValue(eFire));
}

TEST_F(CultsBoardTest, test_increasing_value_by_1_then_2_on_one_track)
{
    CultsBoard cultsBoard;
    ASSERT_EQ(1, cultsBoard.increaseCultValue(eFire, 1));
    ASSERT_EQ(1, cultsBoard.getCultValue(eFire));

    ASSERT_EQ(2, cultsBoard.increaseCultValue(eFire, 2));
    ASSERT_EQ(3, cultsBoard.getCultValue(eFire));
}

TEST_F(CultsBoardTest, test_increasing_value_by_2_then_1_on_one_track)
{
    CultsBoard cultsBoard;
    ASSERT_EQ(2, cultsBoard.increaseCultValue(eFire, 2));
    ASSERT_EQ(2, cultsBoard.getCultValue(eFire));

    ASSERT_EQ(1, cultsBoard.increaseCultValue(eFire, 1));
    ASSERT_EQ(3, cultsBoard.getCultValue(eFire));
}

TEST_F(CultsBoardTest, test_increasing_value_by_2_then_1_on_two_tracks)
{
    CultsBoard cultsBoard;
    ASSERT_EQ(2, cultsBoard.increaseCultValue(eFire, 2));
    ASSERT_EQ(2, cultsBoard.getCultValue(eFire));
    ASSERT_EQ(0, cultsBoard.getCultValue(eWater));

    ASSERT_EQ(1, cultsBoard.increaseCultValue(eWater, 1));
    ASSERT_EQ(1, cultsBoard.getCultValue(eWater));
    ASSERT_EQ(2, cultsBoard.getCultValue(eFire));
    
    ASSERT_EQ(1, cultsBoard.increaseCultValue(eFire, 1));
    ASSERT_EQ(3, cultsBoard.getCultValue(eFire));
    ASSERT_EQ(1, cultsBoard.getCultValue(eWater));
    
    ASSERT_EQ(2, cultsBoard.increaseCultValue(eWater, 2));
    ASSERT_EQ(3, cultsBoard.getCultValue(eFire));
    ASSERT_EQ(3, cultsBoard.getCultValue(eWater));
}

int main(int argc, char* argv[])
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
