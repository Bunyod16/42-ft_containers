#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.hpp"
#include "../vector.hpp"
#include <vector>
#include <iostream>

TEST_CASE("Testing push back") {
    NAME_SPACE::vector<int> myVec;
    myVec.push_back(1);
    myVec.push_back(2);
    CHECK(myVec[0] == 1);
    CHECK(myVec[1] == 2);
}

TEST_CASE("Testing size()") {
    NAME_SPACE::vector<int> myVec;
    myVec.push_back(1);
    myVec.push_back(2);
    CHECK(myVec.size() == 2);
}

TEST_CASE("Initialisation") {
    NAME_SPACE::vector<int> myvec;

    CHECK(myvec.size() == 0);
}

TEST_CASE("Begin") {
    std::vector<int> stdvec(10, 100);
    NAME_SPACE::vector<int> myvec(10, 100);

    CHECK(stdvec.size() == myvec.size());
    CHECK(*stdvec.begin() == *myvec.begin());
    
    CHECK(*stdvec.begin() == *myvec.begin());
}

TEST_CASE("End") {
    NAME_SPACE::vector<int> myvec(10, 100);

    CHECK(10 == myvec.size());
    CHECK(100 == *(myvec.end() - 1) );

    // same with char
    NAME_SPACE::vector<char> myvec2(20, 'c');

    CHECK(20 == myvec2.size());
    myvec2[19] = 'x';
    CHECK('x' == *(myvec2.end() - 1));
}

TEST_CASE("Iterator") {
    std::vector<int> stdvec(10, 100);
    NAME_SPACE::vector<int> myvec(10, 100);

    CHECK(stdvec.size() == myvec.size());
    CHECK(*stdvec.begin() == *myvec.begin());
    
    std::vector<int>::iterator stditer = stdvec.begin();
    NAME_SPACE::vector<int>::iterator myiter = myvec.begin();
    for(; stditer < stdvec.end(); stditer++)
    {
        CHECK(*stditer == *myiter);
        myiter++;
    }

    std::vector<int>::iterator stditer2 = stdvec.begin();
    NAME_SPACE::vector<int>::iterator myiter2 = myvec.begin();
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
    NAME_SPACE::vector<int> ftvec(10);
    CHECK(ftvec.size() == 10);
}

TEST_CASE("Constructor input iterator") {
    std::vector<int> stdvec(10);

   for (unsigned int i = 0; i < stdvec.size(); ++i)
      stdvec[i] = i + 1;

    std::vector<int> stdveccopy(stdvec.begin(), stdvec.end());

   for (unsigned int i = 0; i < stdveccopy.size(); ++i)
        CHECK(stdvec[i] == i + 1);
    
    NAME_SPACE::vector<int> ftvec(10);

   for (unsigned int i = 0; i < ftvec.size(); ++i)
      ftvec[i] = i + 1;

    NAME_SPACE::vector<int> ftveccopy(ftvec.begin(), ftvec.end());

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

    NAME_SPACE::vector<int> ftvec(10, 100);
    NAME_SPACE::vector<int> ftvec2(ftvec);

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

    NAME_SPACE::vector<int> ftvec(10, 100);
    NAME_SPACE::vector<int> ftvec2(10, 100);

    CHECK(ftvec == ftvec2);
    ftvec[0] = 0;
    CHECK(ftvec != ftvec2);
    ftvec[0] = 100;
    CHECK(ftvec == ftvec2);

    NAME_SPACE::vector<int> ftvecempt;
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

    NAME_SPACE::vector<int> ftvec;

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
        NAME_SPACE::vector<int> ftvec;

        CHECK(ftvec.max_size() == stdvec.max_size());
    }
    {
        std::vector<char> stdvec;
        NAME_SPACE::vector<char> ftvec;

        CHECK((ftvec.max_size()) == stdvec.max_size());
    }
    {
        std::vector<std::string> stdvec;
        NAME_SPACE::vector<std::string> ftvec;

        CHECK(ftvec.max_size() == stdvec.max_size());
    }
    {
        std::vector<char **> stdvec;
        NAME_SPACE::vector<char **> ftvec;

        CHECK(ftvec.max_size() == stdvec.max_size());
    }
    {
        std::vector<unsigned char **> stdvec;
        NAME_SPACE::vector<unsigned char **> ftvec;

        CHECK(ftvec.max_size() == stdvec.max_size());
    }
    {
        std::vector<double> stdvec;
        NAME_SPACE::vector<double> ftvec;

        CHECK(ftvec.max_size() == stdvec.max_size());
    }
    {
        std::vector<float> stdvec;
        NAME_SPACE::vector<float> ftvec;

        CHECK(ftvec.max_size() == stdvec.max_size());
    }
}

TEST_CASE("clear") {
    NAME_SPACE::vector<int> vec;
    vec.push_back(1);
    vec.push_back(1);
    vec.push_back(1);
    vec.push_back(1);
    vec.clear();
    CHECK(vec.empty());

    NAME_SPACE::vector<int> vec2;
    vec.clear();
    CHECK(vec.empty());
}

TEST_CASE("pop_back") {
    NAME_SPACE::vector<int> ftvec;

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
    NAME_SPACE::vector<int> ftvec(10, 100);
    NAME_SPACE::vector<int> ftvec2(5, 100);

    ftvec.resize(5);
    CHECK(ftvec == ftvec2);
    ftvec.resize(4);
    CHECK(ftvec != ftvec2);
    ftvec.resize(10, 100);
    ftvec2.resize(10, 100);
    CHECK(ftvec == ftvec2);

}

TEST_CASE("reserve") {
    NAME_SPACE::vector<int> ftvec(10, 100);
    ftvec.reserve(50);
    CHECK(ftvec.capacity() == 50);
}

TEST_CASE("front") {
    NAME_SPACE::vector<int> ftvec(10, 10);
    CHECK(ftvec.front() == 10);
    ftvec[0] = 15;
    CHECK(ftvec.front() == 15);
}

TEST_CASE("back") {
    NAME_SPACE::vector<int> ftvec(10, 10);
    CHECK(ftvec.back() == 10);
    ftvec[9] = 15;
    CHECK(ftvec.back() == 15);
}

TEST_CASE("insert 1") {
    std::vector<int> stdvec(2, 10);
    stdvec.insert(stdvec.begin(), 55);
    stdvec.insert(stdvec.end(), 55);
    stdvec.insert(stdvec.begin() + 2, 55);
    CHECK(stdvec.size() == 5);
    CHECK(stdvec.at(0) == 55);
    CHECK(stdvec.at(2) == 55);
    CHECK(stdvec.at(4) == 55);


    //TODO INSERT
    std::copy(stdvec.begin(), stdvec.end(), std::ostream_iterator<int>(std::cout, " "));

    NAME_SPACE::vector<int> ftvec(2, 10);
    ftvec.insert(ftvec.begin(), 55);
    CHECK(ftvec[0] == 55);
    ftvec.insert(++ftvec.begin(), 55);
    CHECK(ftvec[1] == 55);
}

TEST_CASE("assign 1") {
    NAME_SPACE::vector<char> ftvec(2, 'x');
    ftvec.assign(55, 'I');
    CHECK(ftvec.size() == 55);
    CHECK(ftvec[0] == 'I');
    CHECK(ftvec[15] == 'I');
    CHECK(ftvec[54] == 'I');

    NAME_SPACE::vector<char> ftvec2(5, 'x');
    ftvec2.assign(2, 'I');
    CHECK(ftvec2.size() == 2);
    CHECK(ftvec2[0] == 'I');
    CHECK(ftvec2[1] == 'I');
}

TEST_CASE("assign 2") {
    NAME_SPACE::vector<char> vec;

    vec.push_back('a');
    vec.push_back('b');
    vec.push_back('c');
    vec.push_back('d');
    vec.push_back('e');
    vec.push_back('f');

    NAME_SPACE::vector<char> vec2;

    vec2.push_back('X');
    CHECK(vec2.size() == 1);

    vec2.assign(vec.begin(), vec.end());
    CHECK(vec2.size() == 6);
    CHECK(vec2[0] == 'a');
    CHECK(vec2[5] == 'f');

    NAME_SPACE::vector<char> vec3;

    vec3.push_back('a');
    vec3.push_back('b');
    vec3.push_back('c');
    vec3.push_back('d');
    vec3.push_back('e');
    vec3.push_back('f');
    vec3.push_back('a');
    vec3.push_back('b');
    vec3.push_back('c');
    vec3.push_back('d');
    vec3.push_back('e');
    vec3.push_back('f');

    vec3.assign(vec.begin(), vec.end());

    CHECK(vec3.size() == 6);
}