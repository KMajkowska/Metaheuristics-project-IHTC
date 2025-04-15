#pragma once

#include <unordered_map>
#include <string>

/**
 * @brief This enum is used to communicate through network what type of IWinnerJudge is used
 */
enum class WinnerJudgeType
{
	UNKNOWN,
	BEST_OF_N,
};

const std::unordered_map<WinnerJudgeType, std::string> WJT_ENUM_TO_STRING
{
	{WinnerJudgeType::BEST_OF_N, "Best Of N"},
	{WinnerJudgeType::UNKNOWN, "<empty>"}
};