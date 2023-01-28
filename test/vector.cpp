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

TEST_CASE("Testing size()") {
    ft::vector<int> myVec;
    myVec.push_back(1);
    myVec.push_back(2);
    CHECK(myVec.size() == 2);
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
    
    CHECK(*stdvec.begin() == *myvec.begin());
}

TEST_CASE("End") {
    std::vector<int> stdvec(10, 100);
    ft::vector<int> myvec(10, 100);

    CHECK(stdvec.size() == myvec.size());
    CHECK(*stdvec.end() == *myvec.end());
    
    CHECK(*stdvec.end() == *myvec.end());

    // same with char
    std::vector<char> stdvec2('c', 100);
    ft::vector<char> myvec2('c', 100);

    CHECK(stdvec2.size() == myvec2.size());
    CHECK(*stdvec2.end() == *myvec2.end());
    
    CHECK(*stdvec2.end() == *myvec2.end());
}

TEST_CASE("Iterator") {
    std::vector<int> stdvec(10, 100);
    ft::vector<int> myvec(10, 100);

    CHECK(stdvec.size() == myvec.size());
    CHECK(*stdvec.begin() == *myvec.begin());
    
    std::vector<int>::iterator stditer = stdvec.begin();
    ft::vector<int>::iterator myiter = myvec.begin();
    for(; stditer < stdvec.end(); stditer++)
    {
        CHECK(*stditer == *myiter);
        myiter++;
    }

    std::vector<int>::iterator stditer2 = stdvec.begin();
    ft::vector<int>::iterator myiter2 = myvec.begin();
    for(; myiter2 < myvec.end(); myiter2++)
    {
        CHECK(*stditer2 == *myiter2);
        stditer2++;
    }
    CHECK(stdvec[0] == myvec[0]);
}

TEST_CASE("Constructor input iterator") {
    std::vector<int> stdvec(10);
    CHECK(stdvec.size() == 10);
    ft::vector<int> ftvec(10);
    CHECK(ftvec.size() == 10);
}

TEST_CASE("Constructor input iterator") {
    std::vector<int> stdvec(10);

   for (unsigned int i = 0; i < stdvec.size(); ++i)
      stdvec[i] = i + 1;

    std::vector<int> stdveccopy(stdvec.begin(), stdvec.end());

   for (unsigned int i = 0; i < stdveccopy.size(); ++i)
        CHECK(stdvec[i] == i + 1);
    
    ft::vector<int> ftvec(10);

   for (unsigned int i = 0; i < ftvec.size(); ++i)
      ftvec[i] = i + 1;

    ft::vector<int> ftveccopy(ftvec.begin(), ftvec.end());

   for (unsigned int i = 0; i < ftveccopy.size(); ++i)
        CHECK(ftvec[i] == i + 1);
}


TEST_CASE("Copy constructor") {
    std::vector<int> stdvec(10, 100);
    std::vector<int> stdvec2(stdvec);

    for (unsigned int i = 0; i < stdvec.size(); ++i)
        CHECK(stdvec[i] == stdvec2[i]);
    
    stdvec[0] = 0;
    CHECK(stdvec[0] != stdvec2[0]);

    ft::vector<int> ftvec(10, 100);
    ft::vector<int> ftvec2(ftvec);

    for (unsigned int i = 0; i < ftvec.size(); ++i)
        CHECK(ftvec[i] == ftvec2[i]);
    
    ftvec[0] = 0;
    CHECK(ftvec[0] != ftvec2[0]);
}

TEST_CASE("Operators") {
    // std::vector<int> stdvec(10, 100);
    // std::vector<int> stdvec2(10, 100);

    // CHECK(stdvec == stdvec2);
    // stdvec[0] = 0;
    // CHECK(stdvec != stdvec2);

    ft::vector<int> ftvec(10, 100);
    ft::vector<int> ftvec2(10, 100);

    CHECK(ftvec == ftvec2);
    ftvec[0] = 0;
    CHECK(ftvec != ftvec2);
}