#pragma once

#include <string>
#include <fstream>

#include "ProblemData.h"
#include "SolutionData.h"
#include "CIndividual.h"

class IHTCProblemIO
{
public:
	~IHTCProblemIO() = default;

	static ProblemData parseFromJSON(const std::string& problemFilepath);
	static SolutionData parseToSolution(const CIndividual& individual, const ProblemData& problemData);
	static SolutionData parseFromJSONSolution(const std::string& problemFilepath);
	static std::string parseSolutionToJSON(const SolutionData& solution);

private:
	IHTCProblemIO() = default;

	static constexpr int JSON_INDENT = 4;
};