#pragma once

#include <iostream>
#include <unordered_map>
#include <string>
#include <type_traits>

#include "CoolingSchemeType.h"
#include "NeighbourGeneratorType.h"
#include "SolverType.h"

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
class EnumMapper : public EnumMapperBase<T> {
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
template<>
inline CoolingSchemeType EnumMapper<CoolingSchemeType>::getDefault() const
{
	return CoolingSchemeType::UNKNOWN;
}

template<>
inline NeighbourGeneratorType EnumMapper<NeighbourGeneratorType>::getDefault() const
{
	return NeighbourGeneratorType::UNKNOWN;
}

template<>
inline SolverType EnumMapper<SolverType>::getDefault() const
{
	return SolverType::UNKNOWN;
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