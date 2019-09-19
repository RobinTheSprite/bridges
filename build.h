// build.h
// Created by Mark on 9/18/2019.
//

#ifndef BRIDGES_BUILD_H
#define BRIDGES_BUILD_H

#include <vector>

using Bridge = std::vector<int>;

std::vector<std::vector<Bridge>> subsets(const std::vector<Bridge> &set);

int build(int westCities, int eastCities, const std::vector<Bridge> &bridges);

#endif //BRIDGES_BUILD_H
