#pragma once

#include <string>
#include <fstream>

#include "ProblemData.h"
#include "SolutionData.h"
#include "CIndividual.h"
#include "Params.h"

class IHTCProblemIO
{
public:
	~IHTCProblemIO() = default;

	static ProblemData parseFromJSON(const std::string& problemFilepath);
	static SolutionData parseToSolution(const CIndividual& individual, const ProblemData& problemData);
	static SolutionData parseFromJSONSolution(const std::string& problemFilepath);
	static std::string parseSolutionToJSON(const SolutionData& solution);
	static Params parseParamsFromJSON(const std::string& paramsFilepath);

private:
	IHTCProblemIO() = default;

	static constexpr int JSON_INDENT = 4;
};