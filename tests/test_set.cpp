#include <gtest/gtest.h>
#include <cstdlib>

#include "set.hpp"


class TestSet : public ::testing::Test{
public:

protected:
    struct string_cmp{
        bool operator()(const std::string& lhs, const std::string& rhs) const{
            return lhs < rhs;
        }
    };


    set<int> s_default;
    set<int> s3_int;
    set<int> s4_int;
    set<std::string, string_cmp>s4_str_cmp;
    std::string str_arr[4] = {"2022", "egor", "c++", "qwerty"};


    void SetUp() override{
        for(int i = 0; i < 3; ++i){
            s3_int.insert(i);
        }

        for(int i = 0; i < 4; ++i){
            s4_int.insert(i);
            s4_str_cmp.insert(str_arr[i]);
        }
    }

    void TearDown()override{

    }
    TestSet(): ::testing::Test(){}

};



TEST_F(TestSet, default_constr){
    EXPECT_EQ(s_default.size(), 0);
    EXPECT_TRUE(s_default.empty());
}

TEST_F(TestSet, iterator_constr){

    set<std::string, TestSet::string_cmp>
            test(TestSet::s4_str_cmp.begin(), TestSet::s4_str_cmp.end());

    EXPECT_EQ(*test.begin(), "2022");
    EXPECT_EQ(*(--test.end()), "qwerty");
}
TEST_F(TestSet, init_list_constr){
    set<int> test_int{7,0,1,4,2,6,3,5};
    int check = 0;
    for(auto item: test_int){
        EXPECT_EQ(item, check);
        ++check;
    }
    set<std::string>
    test_str{"7","0","1","4","2","6","3","5"};

    check = 0;
    for(const auto& item: test_str){
        EXPECT_EQ(std::atoi(item.data()), check);
        ++check;
    }
}
TEST_F(TestSet, copy_constr){
    auto test(s3_int);
    EXPECT_EQ(test.size(), s3_int.size());


}
TEST_F(TestSet, move_constr){
    auto test(s3_int);
    auto mv_test(std::move(test));
    EXPECT_TRUE(test.empty());
    EXPECT_EQ(mv_test.size(), s3_int.size());
}
TEST_F(TestSet, operator_equals){
    set<int> test;
    test = s3_int;
    EXPECT_EQ(test.size(), s3_int.size());
}
TEST_F(TestSet, insert){
    s3_int.insert(10);
    EXPECT_EQ(s3_int.size(), 4);
    EXPECT_EQ(*(--s3_int.end()), 10);
}

TEST_F(TestSet, erase){
    s3_int.erase(0);
    EXPECT_EQ(s3_int.size(), 2);
    EXPECT_EQ(*(s3_int.begin()), 1);
}

TEST_F(TestSet, begin) {
    auto test = s3_int.begin();
    EXPECT_EQ(*test, 0);
}

TEST_F(TestSet, end){
    auto test = s3_int.end();
    --test;

    EXPECT_EQ(*s3_int.rbegin(), *test);
}


class TestIterator : public ::testing::Test{
protected:

    set<int> iter_set_10;
    void SetUp() override{
        for(int i = 0; i < 10; ++i){
            iter_set_10.insert(i);
        }
    }

    void TearDown()override{

    }

};

TEST_F(TestIterator, dereferncing){
    auto it = iter_set_10.begin();
    int count = 0;
    for(; it != iter_set_10.end(); ++it){
        EXPECT_EQ(*it, count);
        ++count;
    }
}

TEST_F(TestIterator, prefix_incr){
    auto it = iter_set_10.begin();
    EXPECT_EQ(*(++it), 1);
}

TEST_F(TestIterator, postfix_incr){
    auto it = iter_set_10.begin();
    EXPECT_EQ(*(it++), 0);
}

TEST_F(TestIterator, prefix_decr){
    auto it = iter_set_10.begin();
    ++it;
    EXPECT_EQ(*(--it), 0);
    EXPECT_TRUE(it == iter_set_10.begin());
}

TEST_F(TestIterator, postfix_decr){
    auto it = iter_set_10.begin();
    ++it;
    EXPECT_EQ(*(it--), 1);
}


TEST_F(TestSet, find){
    auto it = s3_int.find(0);
    EXPECT_TRUE(it == s3_int.begin());
    EXPECT_EQ(*it, 0);

    it = s3_int.find(100);
    EXPECT_TRUE(it == s3_int.end());

}

TEST_F(TestSet, lower_bound){
    auto it = s3_int.lower_bound(-1);
    EXPECT_EQ(*it, 0);

    it = s3_int.lower_bound(2);
    EXPECT_EQ(*it, 2);

    it = s3_int.lower_bound(100);
    EXPECT_TRUE(it == s3_int.end());
}
