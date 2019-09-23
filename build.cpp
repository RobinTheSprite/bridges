// build.cpp
// Created by Mark on 9/18/2019.
//

#include "build.h"
#include <vector>
#include <algorithm>
#include <iostream>
using std::vector;

bool subsetContainsCrossedBridges(const vector<Bridge> &subset)
{
    for (auto i = 0; i < subset.size() - 1; ++i)
    {
        for (auto j = i + 1; j <= subset.size() - 1; j++)
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
    vector<std::pair<Bridge, Bridge>> crossedBridges;
    vector<Bridge> currentSubset;

    for (auto nthSubset = 0u; nthSubset < 1u << bridges.size(); ++nthSubset)
    {
        currentSubset.clear();
        for (auto i = 0u; i < bridges.size(); ++i)
        {
            if((nthSubset & (1u << i)) == (1u << i))
            {
                currentSubset.push_back(bridges[i]);
            }
        }

        if(!currentSubset.empty())
        {
            if (subsetContainsCrossedBridges(currentSubset))
            {
                continue;
            }

            auto sumOfTolls = 0;
            vector<int> visitedCitiesWest(westCities, 0);
            vector<int> visitedCitiesEast(eastCities, 0);
            for (auto bridge : currentSubset)
            {
                if (visitedCitiesWest[bridge[0]] == 1 || visitedCitiesEast[bridge[1]] == 1)
                {
                    break;
                }

                visitedCitiesWest[bridge[0]] = 1;
                visitedCitiesEast[bridge[1]] = 1;
                sumOfTolls += bridge[2];
            }

            if (sumOfTolls > maxToll)
            {
                maxToll = sumOfTolls;
            }
        }
    }

    return maxToll;
}