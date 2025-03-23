#pragma once

#include <unordered_map>
#include <string>

/**
 * @brief This class is a marker for the result of a round/game
 */
enum class Winner 
{
	LOCAL,
	OPPONENT,
	DRAW,
	NOT_FINISHED
};

const std::unordered_map<Winner, std::string> WINNER_ENUM_TO_STRING
{
	{Winner::LOCAL, "local"},
	{Winner::OPPONENT, "opponent"},
	{Winner::DRAW, "draw"},
	{Winner::NOT_FINISHED, "not_finished"}
};