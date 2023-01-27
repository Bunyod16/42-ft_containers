#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.hpp"
#include "../vector.hpp"
#include <vector>
#include <iostream>

TEST_CASE("Testing push back") {
    ft::vector<int> myVec;
    myVec.push_back(1);
    myVec.push_back(2);
    CHECK(myVec[0] == 1);
    CHECK(myVec[1] == 2);
}

TEST_CASE("Initialisation") {
    std::vector<int> stdvec;
    ft::vector<int> myvec;

    CHECK(stdvec.size() == myvec.size());
}

TEST_CASE("Begin") {
    std::vector<int> stdvec(10, 100);
    ft::vector<int> myvec(10, 100);

    CHECK(stdvec.size() == myvec.size());
    CHECK(*stdvec.begin() == *myvec.begin());
    CHECK(stdvec[0] == myvec[0]);
}