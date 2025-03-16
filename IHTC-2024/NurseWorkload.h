#pragma once
#include <vector>

class NurseWorkload
{
public:
	NurseWorkload() = default;
	NurseWorkload(std::vector<int> actual, std::vector<int> max);

	void setActualWorkload(std::vector<int>&& actualWorkload);
	void setMaximumWorkload(std::vector<int>&& maximumWorkload);

	std::vector<int>& actualWorkload();
	std::vector<int>& maximumWorkload();

private:
	std::vector<int> _actualWorkload;
	std::vector<int> _maximumWorkload;
};