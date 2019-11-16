// build.cpp
// Created by Mark on 9/18/2019.
//

#include <vector>
#include <algorithm>
#include "build.hpp"
using std::vector;

bool bridgesCross(const Bridge &a, const Bridge &b)
{
    return a[0] == b[0] || a[1] >= b[1];
}

int build(int westCities, int eastCities, const vector<Bridge> &bridges)
{
    vector<Bridge> copyOfBridges = bridges;
    vector<int> maxTollAt(std::max(1ul, bridges.size()));
    std::sort(copyOfBridges.begin(), copyOfBridges.end(), [](auto a, auto b) { return a[0] < b[0]; });

    auto maxToll = 0;
    if (!copyOfBridges.empty())
    {
        maxTollAt[0] = copyOfBridges[0][2];
        maxToll = maxTollAt[0];
        for (auto i = 1ul; i < copyOfBridges.size(); ++i)
        {
            maxTollAt[i] = copyOfBridges[i][2];
            for (auto j = 0ul; j < i; ++j)
            {
                if (!bridgesCross(copyOfBridges[j], copyOfBridges[i]))
                {
                    maxTollAt[i] = std::max(maxTollAt[i], maxTollAt[j] + copyOfBridges[i][2]);
                }
            }
            maxToll = std::max(maxToll, maxTollAt[i]);
        }
    }

    return maxToll;
}