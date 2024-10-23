#pragma once

#include <string>
#include <fstream>

#include "ProblemData.h"
#include "SolutionData.h"
#include "CIndividual.h"

class IHTCProblemIO
{
public:
	IHTCProblemIO() = default;
	~IHTCProblemIO() = default;

	ProblemData parseFromJSON(const std::string& problemFilepath) const;
	SolutionData parseToSolution(const CIndividual& individual, const ProblemData& problemData) const;
	SolutionData parseFromJSONSolution(const std::string& problemFilepath) const;
	std::string parseSolutionToJSON(const SolutionData& solution) const;

private:
	static constexpr int JSON_INDENT = 4;
};