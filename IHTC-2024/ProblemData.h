#pragma once
#include<string>
#include<vector>
#include "WeightsDTO.h"

class ProblemData
{
private:
	int days;
	int skill_levels;
	std::vector<std::string> shift_types;
	std::vector<std::string> age_groups;
	WeightsDTO weights;
};