// build.cpp
// Created by Mark on 9/18/2019.
//

#include <vector>
#include <algorithm>
using std::vector;

bool bridgesCross(const Bridge &a, const Bridge &b)
{
    return a[0] >= b[0] || a[1] >= b[1];
}

int buildRecurse(const vector<Bridge> &bridges, vector<int> &solved, int k)
{
    auto maxToll = 0;

    if (k < bridges.size())
    {
        if (solved[k] != -1)
        {
            return solved[k];
        }

        auto without = buildRecurse(bridges, solved, k + 1);

        auto with = bridges[k][2];
        auto toll = with;
        for (size_t i = k; i < bridges.size(); ++i)
        {
            if (!bridgesCross(bridges[k], bridges[i]))
            {
                toll = std::max(toll, buildRecurse(bridges, solved, i) + with);
            }
        }

        with = toll;
        maxToll = std::max({bridges[k][2], without, with});
        solved[k] = with;
    }

    return maxToll;
}

int build(int westCities, int eastCities, const vector<Bridge> &bridges)
{
    vector<Bridge> copy = bridges;
    vector<Bridge> emptySubset{};
    vector<int> solved(std::max(copy.size(), 1ul), -1);
    std::sort(copy.begin(), copy.end(), [](auto a, auto b) { return a[0] < b[0]; });
    return buildRecurse(copy, solved, 0);
}