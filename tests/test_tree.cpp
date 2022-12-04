#include <gtest/gtest.h>
#include <string>

#include "tree.hpp"

class TestTree : public ::testing::Test{
protected:
    struct string_cmp{
        bool operator()(const std::string& lhs, const std::string& rhs) const {
            return lhs < rhs;
        }
    };

    Tree<int> t_default;
    Tree<int> t3_int;
    Tree<int> t4_int;
    Tree<std::string, string_cmp> t4_str_cmp;
    std::string str_arr[4] = {"2022", "egor", "c++", "qwerty"};

    void SetUp() override{
        for(int i = 0; i < 3; ++i){
            t3_int.insert(i);
        }

        for(int i = 0; i < 4; ++i){
            t4_int.insert(i);
            t4_str_cmp.insert(str_arr[i]);
        }
    }
    void TearDown()override{}
};


TEST_F(TestTree, default_constr){
    EXPECT_EQ(t_default.size(), 0);
    EXPECT_TRUE(t_default.empty());

    EXPECT_EQ(t_default.min_node(), std::shared_ptr<Tree<int>::Node>());
    EXPECT_EQ(t_default.max_node(), std::shared_ptr<Tree<int>::Node>());
}

TEST_F(TestTree, copy_constr){
    Tree<int> test1(t3_int);

    EXPECT_EQ(test1.size(), t3_int.size());
    EXPECT_EQ(test1.empty(), t3_int.empty());
}

TEST_F(TestTree, move_constr){
    Tree<int> test1(t3_int);
    Tree<int> test2(std::move(test1));

    EXPECT_TRUE(test1.empty());
    EXPECT_EQ(test2.size(), t3_int.size());
}

TEST_F(TestTree, search){
    for(int i = 0; i < int(t3_int.size()); ++i){
        EXPECT_EQ(t3_int.search(i)->key, i);
    }

    EXPECT_EQ(t4_str_cmp.search("larkin"), nullptr);
    EXPECT_EQ(t4_str_cmp.search("qwerty")->key, "qwerty");
}

TEST_F(TestTree, insert){
    for(int i = 0; i < 3; ++i){
       t3_int.insert(i);
    }
    EXPECT_EQ(t3_int.size(), 3);

    auto test = t3_int;
    test.insert(3);
    EXPECT_EQ(test.size(), 4);

    for(int i = 0; i < int(test.size()); ++i){
        EXPECT_EQ(test.search(i)->key, i);
    }

    auto test2= t4_str_cmp;
    test2.insert("zoo");
    EXPECT_EQ(test2.size(), 5);

}

TEST_F(TestTree, erase){
    auto test = t3_int;
    test.erase(1);
    EXPECT_EQ(test.size(), t3_int.size()-1);
    EXPECT_EQ(test.search(1), nullptr);
}


TEST_F(TestTree, lower_bound){
    EXPECT_EQ(t3_int.lower_bound(-1)->key, 0);
    EXPECT_EQ(t3_int.lower_bound(0)->key, 0);
    EXPECT_EQ(t3_int.lower_bound(4), nullptr);
}

TEST_F(TestTree, min_node){
    EXPECT_EQ(t3_int.min_node()->key, 0);
    EXPECT_EQ(t4_str_cmp.min_node()->key, "2022");
}

TEST_F(TestTree, max_node){
    EXPECT_EQ(t3_int.max_node()->key, 2);
    EXPECT_EQ(t4_str_cmp.max_node()->key, "qwerty");
}



