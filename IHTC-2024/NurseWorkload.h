#pragma once
#include <vector>

/**
 * @brief Class to store each nurse actual workload generated by patients on given day and shift and here maximum workload on given day and shift. 
 * Based on it the soft restrictions if nurse is overworked is calculated
*/
struct NurseWorkload
{
	NurseWorkload() = default;
	NurseWorkload(std::vector<int> actual, std::vector<int> max) : actualWorkload(actual), maximumWorkload(max){}
	std::vector<int> actualWorkload;
	std::vector<int> maximumWorkload;
};