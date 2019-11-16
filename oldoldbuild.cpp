// build.cpp
// Created by Mark on 9/18/2019.
//

#include <vector>
#include "build.hpp"
using std::vector;

bool containsCrossedBridges(const vector<Bridge> &subset)
{
    for (auto i = 0ul; i < subset.size(); ++i)
    {
        for (auto j = i + 1; j < subset.size(); j++)
        {
            if((subset[i][0] <= subset[j][0] && subset[i][1] >= subset[j][1]) ||
               (subset[i][0] >= subset[j][0] && subset[i][1] <= subset[j][1]))
            {
                return true;
            }
        }
    }

    return false;
}

int build(int westCities, int eastCities, const vector<Bridge> &bridges)
{
    auto maxToll = 0;
    vector<Bridge> currentSubset;

    for (auto nthSubset = 0ul; nthSubset < 1u << bridges.size(); ++nthSubset)
    {
        currentSubset.clear();
        for (auto i = 0ul; i < bridges.size(); ++i)
        {
            if((nthSubset & (1u << i)) == (1u << i))
            {
                currentSubset.push_back(bridges[i]);
            }
        }

        if (containsCrossedBridges(currentSubset))
        {
            continue;
        }

        auto sumOfTolls = 0;
        for (auto bridge : currentSubset)
        {
            sumOfTolls += bridge[2];
        }

        if (sumOfTolls > maxToll)
        {
            maxToll = sumOfTolls;
        }

    }

    return maxToll;
}