// build.cpp
// Created by Mark on 9/18/2019.
//

#include <vector>
#include <algorithm>
#include <numeric>
#include "build.h"
using std::vector;

bool containsCrossedBridges(const vector<Bridge> &subset)
{
    if (subset.size() <= 1)
    {
        return false;
    }

    return subset[subset.size() - 2][0] >= subset.back()[0] || subset[subset.size() - 2][1] >= subset.back()[1];
}

int buildRecurse(const vector<Bridge> &bridges, vector<Bridge> subset, int startIndex)
{
    auto maxToll = 0;
    auto save = subset;

    for (auto i = startIndex; i < bridges.size(); ++i)
    {
        auto toll = 0;
        subset.push_back(bridges[i]);
        if (!containsCrossedBridges(subset))
        {
            toll += bridges[i].back();
            toll += buildRecurse(bridges, subset, i + 1);
            maxToll = std::max(maxToll, toll);
        }
        subset = save;
    }

    return maxToll;
}

int build(int westCities, int eastCities, const vector<Bridge> &bridges)
{
    vector<Bridge> copy = bridges;
    std::sort(copy.begin(), copy.end(), [](auto a, auto b) { return a[0] < b[0]; });
    return buildRecurse(copy, vector<Bridge>{}, 0);
}