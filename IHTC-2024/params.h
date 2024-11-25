#pragma once

#include <string>
#include <nlohmann/json.hpp>

#include "SolverType.h"
#include "NeighbourGeneratorType.h"

static const std::string DEFAULT_PROBLEM_FILE = "../datasets/ihtc2024_test_dataset/test01.json";
static const std::string DEFAULT_PARAMS_FILE = "./params.json";

struct Params
{
	Params() = default;

	std::string outputPath = "./";

	double hardRestrictionWeight = 0.0;

	double mutationProbability = 0.0;
	int neighbourNumber = 0;

	int maxIteration = 0;

	double startingTemperature = 0.0;
	double stopTemperature = 0.0;
	double simplexCoolingMultiplier = 0.0;

	int solverRepetitionAmount = 0;

	SolverType initSolver = SolverType::UNKNOWN;
	SolverType outputSolver = SolverType::UNKNOWN;

	NeighbourGeneratorType neighbourGenerator = NeighbourGeneratorType::UNKNOWN;
};

void to_json(nlohmann::json& j, const Params& data);
void from_json(const nlohmann::json& j, Params& data);