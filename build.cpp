// build.cpp
// Created by Mark on 9/18/2019.
//

#include "build.h"
#include <vector>
#include <set>
#include <algorithm>
#include <iostream>
using std::vector;
using std::set;

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

bool bridgesCross(const vector<Bridge>& bridgeSubset)
{
    return (bridgeSubset[0][0] < bridgeSubset[1][0] && bridgeSubset[0][1] > bridgeSubset[1][1]) ||
            (bridgeSubset[0][0] > bridgeSubset[1][0] && bridgeSubset[0][1] < bridgeSubset[1][1]);
}

bool containsCrossedBridges(const set<std::pair<Bridge, Bridge>>& crossedBridges, const vector<Bridge>&bridgeSubset)
{
    for (const auto& bridgePair : crossedBridges)
    {
        if (std::count(bridgeSubset.begin(), bridgeSubset.end(), bridgePair.first) > 0 &&
            std::count(bridgeSubset.begin(), bridgeSubset.end(), bridgePair.second) > 0)
        {
            return true;
        }
    }

    return false;
}

int build(int westCities, int eastCities, const vector<Bridge> &bridges)
{
    auto maxToll = 0;
    set<std::pair<Bridge, Bridge>> crossedBridges;

    auto bridgeSubsets = subsets(bridges);

    for (const auto& bridgeSubset : bridgeSubsets)
    {
        auto sumOfTolls = 0;
        set<int> visitedCitiesWest;
        set<int> visitedCitiesEast;

        if(bridgeSubset.size() == 2)
        {
            if(bridgesCross(bridgeSubset))
            {
                crossedBridges.insert(std::make_pair(bridgeSubset[0], bridgeSubset[1]));
            }
        }

        if(containsCrossedBridges(crossedBridges, bridgeSubset))
        {
            continue;
        }

        for (auto bridge : bridgeSubset)
        {
            if (visitedCitiesWest.count(bridge[0]) > 0 || visitedCitiesEast.count(bridge[1]) > 0)
            {
                break;
            }

            visitedCitiesWest.insert(bridge[0]);
            visitedCitiesEast.insert(bridge[1]);
            sumOfTolls += bridge[2];
        }

        if(sumOfTolls > maxToll)
        {
            maxToll = sumOfTolls;
        }
    }

    return maxToll;
}