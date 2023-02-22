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
    map.insert(NAME_SPACE::make_pair(1, 'G'));
    CHECK(map[1] == 't');
    CHECK(map[2] == 'e');
    CHECK(map[3] == 's');
    CHECK(map.insert(NAME_SPACE::make_pair(3, 's')).second == false);
    CHECK(map.size() == 3);
}

TEST_CASE("Test insert iterator") {
    NAME_SPACE::map<int, char> map, copy_map;

    map.insert(NAME_SPACE::make_pair(1, 't'));
    map.insert(NAME_SPACE::make_pair(2, 'e'));
    map.insert(NAME_SPACE::make_pair(3, 's'));
    CHECK(map[1] == 't');
    CHECK(map[2] == 'e');
    CHECK(map[3] == 's');

    copy_map.insert(NAME_SPACE::make_pair(1, 'A'));
    copy_map.insert(map.begin(), map.end());
    CHECK(copy_map[1] == 'A');
    CHECK(copy_map[2] == 'e');
    CHECK(copy_map[3] == 's');
    map[1] = 0;
    map[2] = 0;
    map[3] = 0;
    CHECK(copy_map[1] == 'A');
    CHECK(copy_map[2] == 'e');
    CHECK(copy_map[3] == 's');
    CHECK(map[1] == 0);
    CHECK(map[2] == 0);
    CHECK(map[3] == 0);
}

TEST_CASE("Test insert position") {
    NAME_SPACE::map<int, char> map, copy_map;

    map.insert(NAME_SPACE::make_pair(1, 't'));
    map.insert(NAME_SPACE::make_pair(2, 'e'));
    map.insert(NAME_SPACE::make_pair(3, 's'));
    CHECK(map[1] == 't');
    CHECK(map[2] == 'e');
    CHECK(map[3] == 's');

    copy_map.insert(NAME_SPACE::make_pair(1, 'A'));
    copy_map.insert(map.begin(), map.end());
    CHECK(copy_map[1] == 'A');
    CHECK(copy_map[2] == 'e');
    CHECK(copy_map[3] == 's');
    map[1] = 0;
    map[2] = 0;
    map[3] = 0;
    CHECK(copy_map[1] == 'A');
    CHECK(copy_map[2] == 'e');
    CHECK(copy_map[3] == 's');
    CHECK(map[1] == 0);
    CHECK(map[2] == 0);
    CHECK(map[3] == 0);
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

TEST_CASE("Test pre mix iterator -- ++") 
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
        CHECK((++it)->second == 2);
        CHECK((++it) == map.end());
        CHECK((it--) == map.end());
        CHECK((--it)->second == 1);
        CHECK((--it)->second == 0);
}

TEST_CASE("Test clear") {
    NAME_SPACE::map<int, char> map;

    map.insert(NAME_SPACE::make_pair(1, 't'));
    map.insert(NAME_SPACE::make_pair(2, 't'));
    map.insert(NAME_SPACE::make_pair(3, 't'));

    CHECK(map.size() == 3);
    map.clear();
    CHECK(map.empty() == true);
}

TEST_CASE("Test copy constructor") {
    NAME_SPACE::map<int, char> map;

    map.insert(NAME_SPACE::make_pair(1, 't'));
    map.insert(NAME_SPACE::make_pair(2, 't'));
    map.insert(NAME_SPACE::make_pair(3, 't'));

    NAME_SPACE::map<int, char> copy_map(map);
    CHECK(copy_map.size() == 3);
    map.clear();
    CHECK(map.empty() == true);
    CHECK(copy_map.size() == 3);
    CHECK(copy_map.empty() == false);

    NAME_SPACE::map<int, char> empt1;
    NAME_SPACE::map<int, char> empt2(empt1);
    empt1.insert(NAME_SPACE::make_pair(1, 't'));
    empt2.insert(NAME_SPACE::make_pair(1, 'A'));
    empt2.insert(NAME_SPACE::make_pair(2, 'B'));
    CHECK(empt1[1] == 't');
    CHECK(empt2[1] == 'A');
    CHECK(empt2[2] == 'B');
}

TEST_CASE("Test equals") {
    NAME_SPACE::map<int, char> map;

    map.insert(NAME_SPACE::make_pair(1, 't'));
    map.insert(NAME_SPACE::make_pair(2, 't'));
    map.insert(NAME_SPACE::make_pair(3, 't'));

    NAME_SPACE::map<int, char> copy_map;
    copy_map = map;
    CHECK(copy_map.size() == 3);
    map.clear();
    CHECK(map.empty() == true);
    CHECK(copy_map.size() == 3);
    CHECK(copy_map.empty() == false);

    NAME_SPACE::map<int, char> empt1;
    NAME_SPACE::map<int, char> empt2;

    empt1 = empt2;
    empt1.insert(NAME_SPACE::make_pair(1, 't'));
    empt2.insert(NAME_SPACE::make_pair(1, 'A'));
    empt2.insert(NAME_SPACE::make_pair(2, 'B'));
    CHECK(empt1[1] == 't');
    CHECK(empt2[1] == 'A');
    CHECK(empt2[2] == 'B');
}

TEST_CASE("Test erase") {
    {
        NAME_SPACE::map<int, char> map;

        map.insert(NAME_SPACE::make_pair(1, 't'));
        map.insert(NAME_SPACE::make_pair(2, 't'));
        map.insert(NAME_SPACE::make_pair(3, 't'));

        map.erase(1);
        CHECK(map.size() == 2);
        map.insert(NAME_SPACE::make_pair(1, 'A'));
        CHECK(map[1] == 'A');

        NAME_SPACE::map<int, char> empty_map;
        empty_map.erase(1);
    }
    {
        NAME_SPACE::map<int, char> map;
    
        map.insert(NAME_SPACE::make_pair(1, 't'));
        map.insert(NAME_SPACE::make_pair(2, 't'));
        map.insert(NAME_SPACE::make_pair(3, 't'));
        map.insert(NAME_SPACE::make_pair(4, 't'));
        map.insert(NAME_SPACE::make_pair(5, 't'));
        map.insert(NAME_SPACE::make_pair(6, 't'));
        map.insert(NAME_SPACE::make_pair(7, 't'));
        map.insert(NAME_SPACE::make_pair(8, 't'));
        map.insert(NAME_SPACE::make_pair(9, 't'));
        map.insert(NAME_SPACE::make_pair(10, 't'));
        map.insert(NAME_SPACE::make_pair(11, 't'));
        map.insert(NAME_SPACE::make_pair(12, 't'));
    
        map.erase(6);
        CHECK(map.size() == 11);
        CHECK(map[6] != 't');
        map.erase(10);
        CHECK(map[10] != 't');
    
    }
    {
        //erase root
        std::cout << "------- START ----------" << std::endl;
        NAME_SPACE::map<int, char> map;
    
        map.insert(NAME_SPACE::make_pair(1, 't'));
        map.insert(NAME_SPACE::make_pair(2, 't'));
        map.insert(NAME_SPACE::make_pair(3, 't'));
    
        map.erase(2);
        // CHECK(map.size() == 2);
        // CHECK(map[1] == 't');
        // CHECK(map[2] != 't');
        // CHECK(map[3] == 't');
    
    }
}

// TEST_CASE("Test iterator") {
//     NAME_SPACE::map<int, char> map;

//     map.insert(NAME_SPACE::make_pair(1, 't'));
//     map.insert(NAME_SPACE::make_pair(2, 'g'));
//     map.insert(NAME_SPACE::make_pair(3, 'v'));

//     NAME_SPACE::map<int, char>::iterator it = map.begin();

//     CHECK((it++)->first == 1);
//     CHECK((it++)->first == 2);
//     CHECK((it++)->first == 3);
//     CHECK(it == map.end());
//     // CHECK(map2.size() == 0);
// }

TEST_CASE("Test erase 2 iterator") {
    {
        NAME_SPACE::map<int, char> map;

        map.insert(NAME_SPACE::make_pair(1, 't'));
        map.insert(NAME_SPACE::make_pair(2, 'g'));
        map.insert(NAME_SPACE::make_pair(3, 'v'));

        CHECK(map.size() == 3);
        map.erase(map.begin(), map.end());
        CHECK(map.size() == 0);
        map.insert(NAME_SPACE::make_pair(5, 'T'));
        map.insert(NAME_SPACE::make_pair(6, 'G'));
        map.insert(NAME_SPACE::make_pair(7, 'V'));
        CHECK(map.size() == 3);
        CHECK(map[5] == 'T');
        CHECK(map[6] == 'G');
        CHECK(map[7] == 'V');
    }
    {
        NAME_SPACE::map<int, char> map;

        map.insert(NAME_SPACE::make_pair(1, 't'));
        map.insert(NAME_SPACE::make_pair(2, 'g'));
        map.insert(NAME_SPACE::make_pair(3, 'v'));

        CHECK(map.size() == 3);
        map.erase(map.begin(), --map.end());
        CHECK(map.size() == 1);
        CHECK(map.begin()->first == 3);
    }
}

TEST_CASE("Test erase iterator") {
    NAME_SPACE::map<int, char> map;

    map.insert(NAME_SPACE::make_pair(1, 't'));
    map.insert(NAME_SPACE::make_pair(2, 'g'));
    map.insert(NAME_SPACE::make_pair(3, 'v'));

    CHECK(map.size() == 3);
    map.erase(map.begin());

    CHECK(map.size() == 2);
    CHECK(map.begin()->first == 2);

    map.insert(NAME_SPACE::make_pair(6, 'G'));
    map.insert(NAME_SPACE::make_pair(7, 'V'));

    CHECK(map.size() == 4);
    map.erase((++++map.begin()));
    CHECK(map.size() == 3);
    CHECK(map[6] != 'G');
}

TEST_CASE("Test swap") {
    NAME_SPACE::map<int, char> map;
    NAME_SPACE::map<int, char> map2;

    map.insert(NAME_SPACE::make_pair(1, 'a'));
    map.insert(NAME_SPACE::make_pair(2, 'b'));
    map.insert(NAME_SPACE::make_pair(3, 'c'));

    map2.insert(NAME_SPACE::make_pair(5, 'x'));
    map2.insert(NAME_SPACE::make_pair(6, 'y'));
    map2.insert(NAME_SPACE::make_pair(7, 'z'));

    NAME_SPACE::map<int, char>::iterator it = map.begin();
    NAME_SPACE::map<int, char>::iterator it2 = map2.begin();

    map.swap(map2);
    CHECK(map2[1] == 'a');
    CHECK(map[5] == 'x');
    CHECK((++it)->first == 2);
    CHECK((++it2)->first == 6);
}

TEST_CASE("Test count") {
    NAME_SPACE::map<int, char> map;

    map.insert(NAME_SPACE::make_pair(1, 'a'));

    CHECK(map.count(1) == 1);
    CHECK(map.count(0) == 0);

    NAME_SPACE::map<int, char> map2;
    CHECK(map2.count(0) == 0);
    CHECK(map2.count(1) == 0);
    CHECK(map2.count(2) == 0);
    CHECK(map2.count(3) == 0);

}

TEST_CASE("Test find") {
    NAME_SPACE::map<int, char> map;

    map.insert(NAME_SPACE::make_pair(1, 'a'));

    NAME_SPACE::map<int, char>::iterator it;
    
    it = map.find(1);
    CHECK(it->first == 1);
    it = map.find(0);
    CHECK(it == map.end());

    NAME_SPACE::map<int, char>::const_iterator const_it;
    
    const_it = map.find(1);
    CHECK(const_it->first == 1);
    const_it = map.find(0);
    CHECK(const_it == map.end());
}

std::string RandomString(int ch)
{
    char alpha[26] = { 'a', 'b', 'c', 'd', 'e', 'f', 'g',
                          'h', 'i', 'j', 'k', 'l', 'm', 'n',
                          'o', 'p', 'q', 'r', 's', 't', 'u',
                          'v', 'w', 'x', 'y', 'z' };
    std::string result = "";
    for (int i = 0; i<ch; i++)
        result = result + alpha[rand() % 26];
    return result;
}

// TEST_CASE("Test insanity")
// {
    

//     NAME_SPACE::map<std::string, int> map;
//     for (int x = 0; x < 100000; x++)
//     {
//         srand(time(NULL));
//         map.insert(NAME_SPACE::make_pair(RandomString(100), 15));
//     }
//     map.clear();
//     CHECK(map.size() == 0);
    
// }