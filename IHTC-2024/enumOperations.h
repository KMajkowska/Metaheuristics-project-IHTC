#pragma once

#include <iostream>
#include <unordered_map>
#include <string>
#include <type_traits>
#include <qstring.h>

#include "CoolingSchemeType.h"
#include "NeighbourGeneratorType.h"
#include "SolverType.h"
#include "strings.h"
#include "StopCriteriumType.h"
#include "Winner.h"
#include "WinnerJudgeType.h"
#include "GameLevel.h"
#include "GameTimeValues.h"

/**
 * @brief This whole files allows mapping string to enum values 
*/
template <typename T>
concept EnumType = std::is_enum_v<T>;

template <EnumType T> class EnumMapper;

template <EnumType T>
class EnumMapperBase 
{
public:
	virtual T getDefault() const = 0;

	virtual const std::unordered_map<T, std::string>& getMap() const = 0;

	static const std::unordered_map<std::string, T>& getReverseMap()
	{
		static std::unordered_map<std::string, T> reverseMap;
		static bool initialized = false;

		if (!initialized)
		{
			for (const auto& [key, value] : EnumMapper<T>::instance().getMap())
			{
				reverseMap[tolowercase(value)] = key;
			}

			initialized = true;
		}

		return reverseMap;
	}
};

template <EnumType T>
class EnumMapper : public EnumMapperBase<T> 
{
public:
	static const EnumMapper<T>& instance()
	{
		static EnumMapper<T> instance;
		return instance;
	}

	T getDefault() const override;

	const std::unordered_map<T, std::string>& getMap() const override;

private:
	EnumMapper() = default;
};

#pragma region getDefault
template <>
inline CoolingSchemeType EnumMapper<CoolingSchemeType>::getDefault() const
{
	return CoolingSchemeType::UNKNOWN;
}

template <>
inline NeighbourGeneratorType EnumMapper<NeighbourGeneratorType>::getDefault() const
{
	return NeighbourGeneratorType::UNKNOWN;
}

template <>
inline SolverType EnumMapper<SolverType>::getDefault() const
{
	return SolverType::UNKNOWN;
}

template <>
inline StopCriteriumType EnumMapper<StopCriteriumType>::getDefault() const
{
	return StopCriteriumType::UNKNOWN;
}

template <>
inline WinnerJudgeType EnumMapper<WinnerJudgeType>::getDefault() const
{
	return WinnerJudgeType::UNKNOWN;
}

template <>
inline Winner EnumMapper<Winner>::getDefault() const
{
	return Winner::NOT_FINISHED;
}

template <>
inline GameLevel EnumMapper<GameLevel>::getDefault() const
{
	return GameLevel::UNKNOWN;
}

template <>
inline GameTimeValues EnumMapper<GameTimeValues>::getDefault() const
{
	return GameTimeValues::UNKNOWN;
}
#pragma endregion getDefault

#pragma region getMap
template <>
inline const std::unordered_map<CoolingSchemeType, std::string>& EnumMapper<CoolingSchemeType>::getMap() const
{
	return CST_ENUM_TO_STRING;
}

template <>
inline const std::unordered_map<NeighbourGeneratorType, std::string>& EnumMapper<NeighbourGeneratorType>::getMap() const
{
	return NGT_ENUM_TO_STRING;
}

template <>
inline const std::unordered_map<SolverType, std::string>& EnumMapper<SolverType>::getMap() const
{
	return ST_ENUM_TO_STRING;
}

template <>
inline const std::unordered_map<StopCriteriumType, std::string>& EnumMapper<StopCriteriumType>::getMap() const
{
	return SCT_ENUM_TO_STRING;
}

template <>
inline const std::unordered_map<Winner, std::string>& EnumMapper<Winner>::getMap() const
{
	return WINNER_ENUM_TO_STRING;
}

template <>
inline const std::unordered_map<WinnerJudgeType, std::string>& EnumMapper<WinnerJudgeType>::getMap() const
{
	return WJT_ENUM_TO_STRING;
}

template <>
inline const std::unordered_map<GameLevel, std::string>& EnumMapper<GameLevel>::getMap() const
{
	return GL_ENUM_TO_STRING;
}

template <>
inline const std::unordered_map<GameTimeValues, std::string>& EnumMapper<GameTimeValues>::getMap() const
{
	return GTV_ENUM_TO_STRING;
}
#pragma endregion getMap

template <EnumType T>
std::string enumToString(T value)
{
	const auto& map = EnumMapper<T>::instance().getMap();

	auto it = map.find(value);

	if (it != map.end())
	{
		return it->second;
	}

	throw std::invalid_argument("Invalid string value");
}

template <EnumType T>
T stringToEnum(const std::string& str)
{
	const auto& map = EnumMapper<T>::instance().getReverseMap();

	auto it = map.find(tolowercase(str));

	if (it != map.end())
	{
		return it->second;
	}

	return EnumMapper<T>::instance().getDefault();
}

template <EnumType T>
T stringToEnum(QString str)
{
	return stringToEnum<T>(str.toStdString());
}