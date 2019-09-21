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

vector<vector<Bridge>> subsets(const vector<Bridge> &set)
{
    vector<Bridge> subset;
    vector<vector<Bridge>> powerSet;

    for (auto subsetId = 0u; subsetId < 1u << set.size(); ++subsetId)
    {
        for (auto i = 0u; i < set.size(); ++i)
        {
            if((subsetId & (1u << i)) == (1u << i))
            {
                subset.push_back(set[i]);
            }
        }

        powerSet.push_back(subset);
        subset.clear();
    }

    return powerSet;
}

bool subsetContainsCrossedBridges(const vector<std::pair<Bridge, Bridge>> &crossedBridges,
                                  const vector<Bridge> &bridgeSubset)
{
    for (const auto& crossedPair : crossedBridges)
    {
        if (std::find(bridgeSubset.begin(), bridgeSubset.end(), crossedPair.first) != bridgeSubset.end() &&
            std::find(bridgeSubset.begin(), bridgeSubset.end(), crossedPair.second) != bridgeSubset.end())
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

    auto bridgeSubsets = subsets(bridges);

    for (const auto& bridgeSubset : bridgeSubsets)
    {
        if(bridgeSubset.size() == 2)
        {
            if(bridgesCross(bridgeSubset))
            {
                crossedBridges.emplace_back(bridgeSubset[0], bridgeSubset[1]);
                continue;
            }
        }

        if(subsetContainsCrossedBridges(crossedBridges, bridgeSubset))
        {
            continue;
        }

        auto sumOfTolls = 0;
        vector<int> visitedCitiesWest(westCities, 0);
        vector<int> visitedCitiesEast(eastCities, 0);
        for (auto bridge : bridgeSubset)
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
    }

    return maxToll;
}