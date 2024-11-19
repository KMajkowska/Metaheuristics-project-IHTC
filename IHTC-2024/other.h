#pragma once

#include <string>
#include <fstream>
#include <random>
#include <map>
#include <filesystem>

#include "ViolatedRestrictions.h"
#include "WeightsDTO.h"
#include "SolverType.h"
#include "SASolver.h"
#include "GreedySolver.h"
#include "RandomSolver.h"

void writeToFile(const std::string& filename, const std::string& data);

std::mt19937 createRandomGenerator();

std::pair<int, int> findTwoDifferentNumbersBetween(int lowLimit, int highLimit, std::mt19937& generator);

std::string getFileNameWithoutExtension(const std::string& filePath);

IHTCSolver* getSolver(SolverType solverType, SASolver& saSolver, RandomSolver& randSolver, GreedySolver& greedySolver);

template<typename T>
std::ostream& operator<<(std::ostream& os, const std::vector<T>& vec);