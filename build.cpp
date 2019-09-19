// build.cpp
// Created by Mark on 9/18/2019.
//

#include "build.h"

#include <vector>
using std::vector;
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