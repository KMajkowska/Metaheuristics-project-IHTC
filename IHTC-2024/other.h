#pragma once

#include <string>
#include <fstream>
#include <random>
#include <map>
#include <filesystem>

static const std::string LOG_FILE = "../logFiles/";

void writeToFile(const std::string& filename, const std::string& data);

std::mt19937 createRandomGenerator();

std::pair<int, int> findTwoDifferentNumbersBetween(int lowLimit, int highLimit, std::mt19937& generator);

std::string getFileNameWithoutExtension(const std::string& filePath);

std::string getLoggerFileName(const std::string filePath);