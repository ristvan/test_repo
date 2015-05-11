#include "AVLTree.hh"
#include "AVLTreeNodeItem.hh"
#include "gtest/gtest.h"
#include <iostream>

using namespace std;

const int ZERO = 0;

class AVLTreeTest : public ::testing::Test
{
protected:
    virtual void SetUp() { }
    virtual void TearDown() { }
};

TEST_F(AVLTreeTest, test_avl_tree_creation_and_default_values)
{
    AVLTree avlTree;

    EXPECT_EQ(ZERO, avlTree.Count());
}

TEST_F(AVLTreeTest, test)
{
    AVLTree avlTree;
    AVLTreeNodeItem item1(ZERO);

    avlTree.Add(item1);

    EXPECT_EQ(1, avlTree.Count());
}

int main(int argc, char* argv[])
{
    ::testing::InitGoogleTest(&argc, argv);
    cout << "AVLTree Test" << endl;
    return RUN_ALL_TESTS();
}
