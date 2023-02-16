#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.hpp"
#include "../map.hpp"
#include <map>
#include <iostream>

TEST_CASE("Test size") {
    NAME_SPACE::map<int, char> map;

    CHECK(map.size() == 0);
    map.insert(NAME_SPACE::make_pair(1, 't'));
    CHECK(map.size() == 1);
}

TEST_CASE("Test empty") {
    NAME_SPACE::map<int, char> map;

    CHECK(map.empty() == true);
    map.insert(NAME_SPACE::make_pair(1, 't'));
    CHECK(map.empty() == false);
}

TEST_CASE("Test insert") {
    NAME_SPACE::map<int, char> map;

    map.insert(NAME_SPACE::make_pair(1, 't'));
    map.insert(NAME_SPACE::make_pair(2, 'e'));
    map.insert(NAME_SPACE::make_pair(3, 's'));
    CHECK(map[1] == 't');
    CHECK(map[2] == 'e');
    CHECK(map[3] == 's');
}

TEST_CASE("Test at") {
    NAME_SPACE::map<int, char> map;

    map.insert(NAME_SPACE::make_pair(1, 't'));
    map.insert(NAME_SPACE::make_pair(2, 'e'));
    map.insert(NAME_SPACE::make_pair(3, 's'));
    CHECK(map.at(1) == 't');
    CHECK(map.at(2) == 'e');
    CHECK(map.at(3) == 's');
}

TEST_CASE("Test square brace access") {
    {
        NAME_SPACE::map<int, char> map;

        CHECK(map[1] == 0);
        CHECK(map[2] == 0);
        CHECK(map[3] == 0);
        CHECK(map.size() == 3);
    }
    {
        NAME_SPACE::map<int, char> map;
        map.insert(NAME_SPACE::make_pair(10, 'x'));
        CHECK(map[10] == 'x');
    }

}

// TEST_CASE("Test clear") {
//     NAME_SPACE::map<int, char> map;

//     map.insert(NAME_SPACE::make_pair(1, 't'));
//     map.insert(NAME_SPACE::make_pair(2, 'e'));
//     map.insert(NAME_SPACE::make_pair(3, 's'));
//     map.clear();
//     CHECK(map.empty() == true);
// }

TEST_CASE("Test begin") {
    NAME_SPACE::map<int, char> map;

    map.insert(NAME_SPACE::make_pair(1, 't'));
    CHECK((*map.begin()).first == 1);
}

TEST_CASE("Test pre iterator++") 
{
        NAME_SPACE::map<int, char> map;

        map.insert(NAME_SPACE::make_pair(0, 0));
        map.insert(NAME_SPACE::make_pair(1, 1));
        map.insert(NAME_SPACE::make_pair(2, 2));
        map.insert(NAME_SPACE::make_pair(3, 3));

        CHECK(map[0] == 0);
        CHECK(map[1] == 1);
        CHECK(map[2] == 2);

        NAME_SPACE::map<int, char>::iterator it = map.begin();
        int i = 0;
        CHECK((++it)->second == map[i + 1]);
}

TEST_CASE("Test post iterator++") 
{
        NAME_SPACE::map<int, char> map;

        map.insert(NAME_SPACE::make_pair(0, 0));
        map.insert(NAME_SPACE::make_pair(1, 1));
        map.insert(NAME_SPACE::make_pair(2, 2));
        CHECK(map[0] == 0);
        CHECK(map[1] == 1);
        CHECK(map[2] == 2);
        NAME_SPACE::map<int, char>::iterator it = map.begin();

        int i = 0;
        while (it != map.end())
        {
            std::cout << "KEY: " << it->first << std::endl;
            CHECK(map[i] == i);
            CHECK((it++)->second == i);
            i++;
        }
}

TEST_CASE("Test post iterator--") 
{
        NAME_SPACE::map<int, char> map;

        map.insert(NAME_SPACE::make_pair(0, 0));
        map.insert(NAME_SPACE::make_pair(1, 1));
        map.insert(NAME_SPACE::make_pair(2, 2));
        CHECK(map[0] == 0);
        CHECK(map[1] == 1);
        CHECK(map[2] == 2);
        NAME_SPACE::map<int, char>::iterator it = map.end();

        it--;
        CHECK((it--)->second == 2);
        CHECK((it--)->second == 1);
        CHECK(it->second == 0);
}

TEST_CASE("Test pre iterator--") 
{
        NAME_SPACE::map<int, char> map;

        map.insert(NAME_SPACE::make_pair(0, 0));
        map.insert(NAME_SPACE::make_pair(1, 1));
        map.insert(NAME_SPACE::make_pair(2, 2));
        CHECK(map[0] == 0);
        CHECK(map[1] == 1);
        CHECK(map[2] == 2);
        NAME_SPACE::map<int, char>::iterator it = map.end();

        
        CHECK((--it)->second == 2);
        CHECK((--it)->second == 1);
}