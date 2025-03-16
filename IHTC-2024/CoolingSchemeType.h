#pragma once

#include <unordered_map>
#include <string>

/**
 * @brief Enum for choosing cooling scheme 
*/
enum class CoolingSchemeType
{
	GEMAN_AND_GEMAN,
	SIMPLEX,
	VARIABLE,
	UNKNOWN
};

const std::unordered_map<CoolingSchemeType, std::string> CST_ENUM_TO_STRING
{
	{CoolingSchemeType::GEMAN_AND_GEMAN, "gemanAndGeman"},
	{CoolingSchemeType::SIMPLEX, "simplex"},
	{CoolingSchemeType::VARIABLE, "variable"},
};
