#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.hpp"
// #include "../map.hpp"
#include <map>
#include <iostream>

TEST_CASE("Testing push back") {
    NAME_SPACE::map<int, char> map;

    map.insert(NAME_SPACE::make_pair(1, 'a'));
    map.insert(NAME_SPACE::make_pair(2, 'a'));
    map.insert(NAME_SPACE::make_pair(3, 'a'));
    CHECK(map[1] == 'a');
    CHECK(map[2] == 'b');
    CHECK(map[3] == 'c');
}