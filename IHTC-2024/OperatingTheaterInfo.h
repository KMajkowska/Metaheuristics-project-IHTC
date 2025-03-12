#pragma once

#include <string>

/**
 * @brief Class where we store the info about OT maximum surgeries time aand actual sum of surgeries time
 * Based on it hard restriction if OT is overcrowded is calculated 
*/
struct OperatingTheaterInfo
{
	OperatingTheaterInfo(int max, int current, const std::string& id);

	int max;
	int current;
	std::string id;
};