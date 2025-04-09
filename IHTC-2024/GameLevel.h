#pragma once

#include <unordered_map>
#include <string>

enum class GameLevel
{
	EASY,
	MEDIUM,
	HARD,
	UNKNOWN
};

const std::unordered_map<GameLevel, std::string> GL_ENUM_TO_STRING
{
	{GameLevel::EASY, "Easy"},
	{GameLevel::MEDIUM, "Medium"},
	{GameLevel::HARD, "Hard"},
	{GameLevel::UNKNOWN, "<empty>"}
};