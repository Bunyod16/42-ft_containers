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
    std::vector<int> stdvec(10, 100);
    std::vector<int> stdvec2(10, 100);

    CHECK(stdvec == stdvec2);
    stdvec[0] = 0;
    CHECK(stdvec != stdvec2);

    ft::vector<int> ftvec(10, 100);
    ft::vector<int> ftvec2(10, 100);

    CHECK(ftvec == ftvec2);
    ftvec[0] = 0;
    CHECK(ftvec != ftvec2);
    ftvec[0] = 100;
    CHECK(ftvec == ftvec2);

    ft::vector<int> ftvecempt;
    CHECK(ftvec != ftvecempt);
    CHECK(!(ftvec == ftvecempt));
}

TEST_CASE("at") {
    std::vector<int> stdvec;

    stdvec.push_back(1);
    stdvec.push_back(2);
    stdvec.push_back(3);
    CHECK(stdvec.at(0) == 1);
    CHECK(stdvec.at(1) == 2);
    CHECK(stdvec.at(2) == 3);

    ft::vector<int> ftvec;

    ftvec.push_back(1);
    ftvec.push_back(2);
    ftvec.push_back(3);
    CHECK(ftvec.at(0) == 1);
    CHECK(ftvec.at(1) == 2);
    CHECK(ftvec.at(2) == 3);
}

TEST_CASE("max_size") {
    {
        std::vector<int> stdvec;
        ft::vector<int> ftvec;

        CHECK(ftvec.max_size() == stdvec.max_size());
    }
    {
        std::vector<char> stdvec;
        ft::vector<char> ftvec;

        CHECK((ftvec.max_size()) == stdvec.max_size());
    }
    {
        std::vector<std::string> stdvec;
        ft::vector<std::string> ftvec;

        CHECK(ftvec.max_size() == stdvec.max_size());
    }
    {
        std::vector<char **> stdvec;
        ft::vector<char **> ftvec;

        CHECK(ftvec.max_size() == stdvec.max_size());
    }
    {
        std::vector<unsigned char **> stdvec;
        ft::vector<unsigned char **> ftvec;

        CHECK(ftvec.max_size() == stdvec.max_size());
    }
    {
        std::vector<double> stdvec;
        ft::vector<double> ftvec;

        CHECK(ftvec.max_size() == stdvec.max_size());
    }
    {
        std::vector<float> stdvec;
        ft::vector<float> ftvec;

        CHECK(ftvec.max_size() == stdvec.max_size());
    }
}

TEST_CASE("pop_back") {
    std::vector<int> stdvec;

    stdvec.push_back(1);
    stdvec.push_back(2);
    stdvec.push_back(3);
    CHECK(stdvec.at(stdvec.size() - 1) == 3);
    stdvec.pop_back();
    CHECK(stdvec.at(stdvec.size() - 1) == 2);
    stdvec.pop_back();
    CHECK(stdvec.at(stdvec.size() - 1) == 1);
    stdvec.pop_back();
    CHECK(stdvec.empty());

    ft::vector<int> ftvec;

    ftvec.push_back(1);
    ftvec.push_back(2);
    ftvec.push_back(3);
    CHECK(ftvec.at(ftvec.size() - 1) == 3);
    ftvec.pop_back();
    CHECK(ftvec.at(ftvec.size() - 1) == 2);
    ftvec.pop_back();
    CHECK(ftvec.at(ftvec.size() - 1) == 1);
    ftvec.pop_back();
    CHECK(ftvec.empty());

}


TEST_CASE("resize") {
    std::vector<int> stdvec(10, 100);
    std::vector<int> stdvec2(5, 100);

    stdvec.resize(5);
    CHECK(stdvec == stdvec2);
    stdvec.resize(4);
    CHECK(stdvec != stdvec2);
    stdvec.resize(10, 100);
    stdvec2.resize(10, 100);
    CHECK(stdvec == stdvec2);

    ft::vector<int> ftvec(10, 100);
    ft::vector<int> ftvec2(5, 100);

    ftvec.resize(5);
    CHECK(ftvec == ftvec2);
    ftvec.resize(4);
    CHECK(ftvec != ftvec2);
    ftvec.resize(10, 100);
    ftvec2.resize(10, 100);
    CHECK(ftvec == ftvec2);

}

TEST_CASE("reserve") {
    std::vector<int> stdvec(10, 100);
    stdvec.reserve(50);
    CHECK(stdvec.capacity() == 50);


    ft::vector<int> ftvec(10, 100);
    ftvec.reserve(50);
    CHECK(ftvec.capacity() == 50);
}

TEST_CASE("front") {
    std::vector<int> stdvec(10, 10);
    CHECK(stdvec.front() == 10);
    stdvec[0] = 15;
    CHECK(stdvec.front() == 15);

    ft::vector<int> ftvec(10, 10);
    CHECK(ftvec.front() == 10);
    ftvec[0] = 15;
    CHECK(ftvec.front() == 15);
}

TEST_CASE("back") {
    std::vector<int> stdvec(10, 10);
    CHECK(stdvec.back() == 10);
    stdvec[9] = 15;
    CHECK(stdvec.back() == 15);

    ft::vector<int> ftvec(10, 10);
    CHECK(ftvec.back() == 10);
    ftvec[9] = 15;
    CHECK(ftvec.back() == 15);
}

TEST_CASE("insert 1") {
    std::vector<int> stdvec(2, 10);
    std::cout << stdvec[0] << " " << stdvec[1] << std::endl;
    stdvec.insert(stdvec.begin(), 55);
    std::cout << stdvec[0] << " " << stdvec[1] << std::endl;
    CHECK(stdvec[0] == 55);
    stdvec.insert(++stdvec.begin(), 55);
    std::cout << stdvec[0] << " " << stdvec[1] << std::endl;
    CHECK(stdvec[1] == 55);

    ft::vector<int> ftvec(2, 10);
    ftvec.insert(ftvec.begin(), 55);
    CHECK(ftvec[0] == 55);
    ftvec.insert(++ftvec.begin(), 55);
    CHECK(ftvec[1] == 55);
}