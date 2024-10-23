#pragma once
#include <vector>

struct NurseWorkload
{
	NurseWorkload() = default;
	NurseWorkload(std::vector<int> actual, std::vector<int> max) : actualWorkload(actual), maximumWorkload(max){}
	std::vector<int> actualWorkload;
	std::vector<int> maximumWorkload;
};