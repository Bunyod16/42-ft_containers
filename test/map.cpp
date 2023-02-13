#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.hpp"
#include "../map.hpp"
#include <map>
#include <iostream>

TEST_CASE("Testing push back") {
    NAME_SPACE::map<int, char> map;

    map.insert(NAME_SPACE::make_pair(1, 't'));
    map.insert(NAME_SPACE::make_pair(2, 'e'));
    map.insert(NAME_SPACE::make_pair(3, 's'));
    CHECK(map[1] == 't');
    CHECK(map[2] == 'e');
    CHECK(map[3] == 's');
}