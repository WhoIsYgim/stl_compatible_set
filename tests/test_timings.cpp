#include <gtest/gtest.h>

#include <set>
#include <chrono>
#include <iostream>

#include "set.hpp"



class TestTree : public ::testing::Test {
protected:

    void SetUp() override{
    }

    void TearDown() override{}

};

template <class Set>
void fill_set(Set& set_, const int N){
    for(int i = 0; i < N; ++i){
        set_.insert(i);
    }
}

void test_time_insert(const int N){
    std::set<int> std_set;
    auto start1 = std::chrono::high_resolution_clock::now();
    fill_set(std_set, N);
    auto end1 = std::chrono::high_resolution_clock::now();

    set<int> set;
    auto start2 = std::chrono::high_resolution_clock::now();
    fill_set(set, N);
    auto end2 = std::chrono::high_resolution_clock::now();

    auto dur1 = std::chrono::duration_cast<std::chrono::microseconds>(end1 - start1);
    auto dur2 = std::chrono::duration_cast<std::chrono::microseconds>(end2 - start2);
    std::cout << "std::set insertion " << N << " elements: " << dur1.count() << std::endl;
    std::cout << "set insertion " << N << " elements: " << dur2.count() << std::endl << std::endl;
}

void test_time_erase(const int N){
    std::set<int> std_set;
    fill_set(std_set, N);

    auto start1 = std::chrono::high_resolution_clock::now();
    for(int i = 0; i < N; ++i){
        std_set.erase(i);
    }
    auto end1 = std::chrono::high_resolution_clock::now();

    set<int> set;
    fill_set(set, N);

    auto start2 = std::chrono::high_resolution_clock::now();
    for(int i = 0; i < N; ++i){
        set.erase(i);
    }
    auto end2 = std::chrono::high_resolution_clock::now();

    auto dur1 = std::chrono::duration_cast<std::chrono::microseconds>(end1 - start1);
    auto dur2 = std::chrono::duration_cast<std::chrono::microseconds>(end2 - start2);
    std::cout << "std::set erase " << N << " elements: " << dur1.count() << std::endl;
    std::cout << "set erase " << N << " elements: " << dur2.count() << std::endl << std::endl;
}

void test_time_find(const int N){
    std::set<int> std_set;
    fill_set(std_set, N);

    auto start1 = std::chrono::high_resolution_clock::now();
    for(int i = 0; i < N; ++i){
        std_set.find(i);
    }
    auto end1 = std::chrono::high_resolution_clock::now();

    set<int> set;
    fill_set(set, N);
    auto start2 = std::chrono::high_resolution_clock::now();
    for(int i = 0; i < N; ++i){
        set.find(i);
    }
    auto end2 = std::chrono::high_resolution_clock::now();

    auto dur1 = std::chrono::duration_cast<std::chrono::microseconds>(end1 - start1);
    auto dur2 = std::chrono::duration_cast<std::chrono::microseconds>(end2 - start2);
    std::cout << "std::set find " << N << " elements: " << dur1.count() << std::endl;
    std::cout << "set find " << N << " elements: " << dur2.count() << std::endl << std::endl;
}

void test_time_iteration(const int N){
    std::set<int> std_set;
    fill_set(std_set, N);

    auto start1 = std::chrono::high_resolution_clock::now();
    for(auto item: std_set){
    }
    auto end1= std::chrono::high_resolution_clock::now();

    set<int> set;
    fill_set(set, N);

    auto start2 = std::chrono::high_resolution_clock::now();
    for(auto item: set){
    }
    auto end2 = std::chrono::high_resolution_clock::now();

    auto dur1 = std::chrono::duration_cast<std::chrono::microseconds>(end1 - start1);
    auto dur2 = std::chrono::duration_cast<std::chrono::microseconds>(end2 - start2);
    std::cout << "std::set iteration " << N << " elements: " << dur1.count() << std::endl;
    std::cout << "set iteration " << N << " elements: " << dur2.count() << std::endl << std::endl;
}

TEST(compare, insertion_compare_10){
    test_time_insert(10);
}

TEST(compare, insertion_compare_100){
    test_time_insert(100);
}

TEST(compare, insertion_compare_1000){
    test_time_insert(1000);
}


TEST(compare, insertion_compare_10000){
    test_time_insert(10000);
}

TEST(compare, insertion_compare_100000){
    test_time_insert(100000);
}


TEST(compare, erase_compare_100){
    test_time_erase(100);
}


TEST(compare, erase_compare_1000){
    test_time_erase(1000);
}


TEST(compare, erase_compare_10000){
    test_time_erase(10000);
}

TEST(compare, find_compare_100){
    test_time_find(100);
}

TEST(compare, find_compare_1000){
    test_time_find(1000);
}

TEST(compare, find_compare_10000){
    test_time_find(10000);
}

TEST(compare, iter_compare_100){
    test_time_iteration(100);
}

TEST(compare, iter_compare_1000){
    test_time_iteration(1000);
}

TEST(compare, iter_compare_10000){
    test_time_iteration(10000);}

