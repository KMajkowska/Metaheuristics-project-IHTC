#pragma once

#include <string>

struct OperatingTheaterInfo
{
	OperatingTheaterInfo(int max, int current, const std::string& id);

	int max;
	int current;
	std::string id;
};