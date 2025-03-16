#pragma once

#include <unordered_map>
#include <string>

#include "strings.h"

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

const std::string GEMAN_AND_GEMAN = "gemanAndGeman";
const std::string SIMPLEX = "simplex";
const std::string VARIABLE = "variable";

const std::unordered_map<std::string, CoolingSchemeType> CST_STRING_TO_ENUM
{
	{GEMAN_AND_GEMAN, CoolingSchemeType::GEMAN_AND_GEMAN},
	{SIMPLEX, CoolingSchemeType::SIMPLEX},
	{VARIABLE, CoolingSchemeType::VARIABLE},
};

const std::unordered_map<CoolingSchemeType, std::string> CST_ENUM_TO_STRING
{
	{CoolingSchemeType::GEMAN_AND_GEMAN, GEMAN_AND_GEMAN},
	{CoolingSchemeType::SIMPLEX, SIMPLEX},
	{CoolingSchemeType::VARIABLE, VARIABLE},
};
