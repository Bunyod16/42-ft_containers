#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.hpp"
#include "../map.hpp"
#include <map>
#include <iostream>

TEST_CASE("Test insert") {
    NAME_SPACE::map<int, char> map;

    map.insert(NAME_SPACE::make_pair(1, 't'));
    map.insert(NAME_SPACE::make_pair(2, 'e'));
    map.insert(NAME_SPACE::make_pair(3, 's'));
    CHECK(map[1] == 't');
    CHECK(map[2] == 'e');
    CHECK(map[3] == 's');
}

TEST_CASE("Test square brace access") {
    NAME_SPACE::map<int, char> map;

    CHECK(map[1] == 0);
    CHECK(map[2] == 0);
    CHECK(map[3] == 0);
    CHECK(map.size() == 3);
}