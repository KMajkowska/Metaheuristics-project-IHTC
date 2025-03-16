#include "ShiftDTO.h"

int ShiftDTO::day() const
{
    return _day;
}

std::string ShiftDTO::shift() const
{
    return _shift;
}

int ShiftDTO::maxLoad() const
{
    return _maxLoad;
}

void ShiftDTO::setDay(int newDay)
{
    _day = newDay;
}

void ShiftDTO::setShift(const std::string& newShift)
{
    _shift = newShift;
}

void ShiftDTO::setMaxLoad(int newMaxLoad)
{
    _maxLoad = newMaxLoad;
}

void to_json(nlohmann::json& j, const ShiftDTO& shift)
{
	j = nlohmann::json
	{
		{"day", shift.day()},
		{"shift", shift.shift()},
		{"max_load", shift.maxLoad()}
	};
}

void from_json(const nlohmann::json& j, ShiftDTO& shift)
{
	shift.setDay(j.at("day").get<int>());
	shift.setShift(j.at("shift").get<std::string>());
	shift.setMaxLoad(j.at("max_load").get<int>());

}
