#include <iostream>
#include "vector.hpp"

int main(void)
{
    ft::vector<int> myVec;
    myVec.push_back(1);
    myVec.push_back(2);
    std::cout << myVec[0] << myVec[1] << std::endl;
}