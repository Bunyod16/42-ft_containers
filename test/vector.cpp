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
    NAME_SPACE::vector<int> vec;

    vec.push_back(1);
    vec.push_back(2);
    vec.push_back(3);
    CHECK(vec.at(vec.size() - 1) == 3);
    vec.pop_back();
    CHECK(vec.at(vec.size() - 1) == 2);
    vec.pop_back();
    CHECK(vec.at(vec.size() - 1) == 1);
    vec.pop_back();
    CHECK(vec.empty());
}


TEST_CASE("resize") {
    NAME_SPACE::vector<int> vec(10, 100);
    NAME_SPACE::vector<int> vec2(5, 100);

    vec.resize(5);
    CHECK(vec == vec2);
    vec.resize(4);
    CHECK(vec != vec2);
    vec.resize(10, 100);
    vec2.resize(10, 100);
    CHECK(vec == vec2);

}

TEST_CASE("reserve") {
    NAME_SPACE::vector<int> vec(10, 100);
    vec.reserve(50);
    CHECK(vec.capacity() == 50);
}

TEST_CASE("front") {
    NAME_SPACE::vector<int> vec(10, 10);
    CHECK(vec.front() == 10);
    vec[0] = 15;
    CHECK(vec.front() == 15);
}

TEST_CASE("back") {
    NAME_SPACE::vector<int> vec(10, 10);
    CHECK(vec.back() == 10);
    vec[9] = 15;
    CHECK(vec.back() == 15);
}

TEST_CASE("insert 1") {
    NAME_SPACE::vector<int> vec(2, 10);
    vec.insert(vec.begin(), 55);
    vec.insert(vec.end(), 55);
    vec.insert(vec.begin() + 2, 55);
    CHECK(vec.size() == 5);
    CHECK(vec.at(0) == 55);
    CHECK(vec.at(2) == 55);
    CHECK(vec.at(4) == 55);
}

TEST_CASE("insert 2") {
    NAME_SPACE::vector<int> vec(2, 10);
    vec.insert(vec.begin() + 1, 3, 55);
    CHECK(vec.size() == 5);
    CHECK(vec.at(1) == 55);
    CHECK(vec.at(2) == 55);
    CHECK(vec.at(3) == 55);
}

TEST_CASE("insert 3") {
    NAME_SPACE::vector<int> vec(2, 10);
    NAME_SPACE::vector<int> vec2(3, 5);

    vec.insert(vec.begin() + 1, vec2.begin(),vec2.end());
    CHECK(vec.size() == 5);
    CHECK(vec.at(1) == 5);
    CHECK(vec.at(2) == 5);
    CHECK(vec.at(3) == 5);
}

TEST_CASE("assign 1") {
    NAME_SPACE::vector<char> vec(2, 'x');
    vec.assign(55, 'I');
    CHECK(vec.size() == 55);
    CHECK(vec[0] == 'I');
    CHECK(vec[15] == 'I');
    CHECK(vec[54] == 'I');

    NAME_SPACE::vector<char> vec2(5, 'x');
    vec2.assign(2, 'I');
    CHECK(vec2.size() == 2);
    CHECK(vec2[0] == 'I');
    CHECK(vec2[1] == 'I');
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

TEST_CASE("erase 1") {
    {
        NAME_SPACE::vector<char> vec(5, 'x');

        vec[0] = 'A';
        vec.erase(vec.begin());
        CHECK(vec.size() == 4);
        CHECK(vec[0] == 'x');
        CHECK(vec[1] == 'x');
        CHECK(vec[2] == 'x');
        CHECK(vec[3] == 'x');
    }
    {
        NAME_SPACE::vector<char> vec(5, 'x');
        NAME_SPACE::vector<char>::iterator beg = vec.begin();

        vec[4] = 'A';
        vec[0] = 'A';
        vec.erase(vec.end() - 1);
        vec.erase(beg);
        CHECK(vec.size() == 3);
        CHECK(vec[0] == 'x');
        CHECK(vec[1] == 'x');
        CHECK(vec[2] == 'x');
    }
}

// TEST_CASE("erase 2") {
//     {
//         // NAME_SPACE::vector<char> vec(5, 'x');

//         // vec[0] = 'A';
//         // vec.erase(vec.begin(), vec.end());
//         // CHECK(vec.size() == 0);
//     }
//     {
//         // NAME_SPACE::vector<int> vec;

//         // vec.push_back(1);
//         // vec.push_back(2);
//         // vec.push_back(3);

//         // vec.erase(vec.begin() + 1, vec.end());
//         // CHECK(vec.size() == 1);
//         // CHECK(vec[0] == 1);
//     }
//     {
//         NAME_SPACE::vector<char> vec(5, 'x');
//         NAME_SPACE::vector<char>::iterator beg = vec.begin();

//         vec[0] = 'G';
//         vec[1] = 'A';
//         vec.erase(vec.begin() + 2, vec.end());
//         CHECK(vec.size() == 2);
//         CHECK(vec[0] == 'G');
//         CHECK(vec[1] == 'A');
//         CHECK(*beg == 'G');
//     }
// }

TEST_CASE("swap") {
    {
        NAME_SPACE::vector<int> vec;
        NAME_SPACE::vector<int> vec2;

        vec.push_back(1);
        vec.push_back(2);

        vec2.push_back(3);
        vec2.push_back(4);
        vec2.push_back(5);

        CHECK(vec[0] == 1);
        CHECK(vec[1] == 2);

        CHECK(vec2[0] == 3);
        CHECK(vec2[1] == 4);
        CHECK(vec2[2] == 5);

        vec.swap(vec2);

        CHECK(vec2[0] == 1);
        CHECK(vec2[1] == 2);

        CHECK(vec[0] == 3);
        CHECK(vec[1] == 4);
        CHECK(vec[2] == 5);
    }
}

//TODO swap test
