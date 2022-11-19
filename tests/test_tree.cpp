#include <gtest/gtest.h>
#include "tree.hpp"


class TestTree : public ::testing::Test {
protected:

    void SetUp() override{
    }

    void TearDown() override{}

};

TEST_F(TestTree, default_constr){
    Tree<int> a;

}


TEST_F(TestTree, copy_constr){

}

TEST_F(TestTree, move_constr){

}

TEST_F(TestTree, insert){

}

TEST_F(TestTree, search){

}

TEST_F(TestTree, erase){

}

TEST_F(TestTree, lower_bound){

}




