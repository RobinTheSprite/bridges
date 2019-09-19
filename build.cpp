// build.cpp
// Created by Mark on 9/18/2019.
//

#include "build.h"

#include <vector>
using std::vector;
#include <set>
using std::set;
#include <iostream>

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

}

int build(const vector<Bridge> &bridges)
{
    auto maxToll = 0;

    auto bridgeSubsets = subsets(bridges);

    for (const auto& bridgeSubset : bridgeSubsets)
    {
        auto sumOfTolls = 0;
        set<int> visitedCitiesWest;
        set<int> visitedCitiesEast;

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