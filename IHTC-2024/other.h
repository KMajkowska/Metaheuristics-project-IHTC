#pragma once

#include <string>
#include <fstream>
#include <random>

void writeToFile(const std::string& filename, const std::string& data);

std::mt19937 createRandomGenerator();

std::pair<int, int> findTwoDifferentNumbersBetween(int lowLimit, int highLimit, std::mt19937& generator);