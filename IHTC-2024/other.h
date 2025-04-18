#pragma once

#include <string>
#include <fstream>
#include <random>
#include <map>
#include <filesystem>

void writeToFile(const std::string& filename, const std::string& data);

std::pair<int, int> findTwoDifferentNumbersBetween(int lowLimit, int highLimit, std::mt19937& generator);

std::string getFileNameWithoutExtension(const std::string& filePath);

template<typename T>
std::ostream& operator<<(std::ostream& os, const std::vector<T>& vec);

double calcAverage(const std::vector<double>& data);

double calcStdDev(const std::vector<double>& data);