#pragma once

#include <string>
#include <fstream>

#include "ProblemData.h"

class IHTCProblemReader
{
public:
	IHTCProblemReader() = default;
	~IHTCProblemReader() = default;

	ProblemData parseFromJSON(const std::string& problemFilepath);
};