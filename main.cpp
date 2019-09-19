#include <iostream>
#include "build.h"

using std::cout;
using std::endl;

int main()
{
    std::vector<Bridge> bridges{{0,1,3},{1,1,5},{1,2,4},{2,0,8}};

    int toll = build(bridges);
    if (toll == 8)
    {
        cout << "It works!" << endl;
    }
    else
    {
        cout << "Dang it!" << endl;
        cout << "Toll: " << toll << endl;
    }

    return 0;
}