// build.cpp
// Created by Mark on 9/18/2019.
//

#include "build.h"
#include <vector>
#include <algorithm>
#include <iostream>
using std::vector;

bool bridgesCross(const vector<Bridge>& bridgeSubset)
{
    return (bridgeSubset[0][0] < bridgeSubset[1][0] && bridgeSubset[0][1] > bridgeSubset[1][1]) ||
           (bridgeSubset[0][0] > bridgeSubset[1][0] && bridgeSubset[0][1] < bridgeSubset[1][1]);
}

bool subsetContainsCrossedBridges(const vector<std::pair<Bridge, Bridge>> &crossedBridges,
                                  const vector<Bridge> &subset)
{
    for (const auto& crossedPair : crossedBridges)
    {
        if (std::find(subset.begin(), subset.end(), crossedPair.first) != subset.end() &&
            std::find(subset.begin(), subset.end(), crossedPair.second) != subset.end())
        {
            return true;
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
        for (auto i = 0u; i < bridges.size(); ++i)
        {
            if((nthSubset & (1u << i)) == (1u << i))
            {
                currentSubset.push_back(bridges[i]);
            }
        }

        if(currentSubset.size() == 2)
        {
            if(bridgesCross(currentSubset))
            {
                crossedBridges.emplace_back(currentSubset[0], currentSubset[1]);
                currentSubset.clear();
                continue;
            }
        }

        if(subsetContainsCrossedBridges(crossedBridges, currentSubset))
        {
            currentSubset.clear();
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

        if(sumOfTolls > maxToll)
        {
            maxToll = sumOfTolls;
        }

        currentSubset.clear();
    }

    return maxToll;
}