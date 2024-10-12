#include "ShiftDTO.h"

int ShiftDTO::getDay() const
{
    return day;
}

std::string ShiftDTO::getShift() const
{
    return shift;
}

int ShiftDTO::getMaxLoad() const
{
    return max_load;
}

void ShiftDTO::setDay(int newDay)
{
    day = newDay;
}

void ShiftDTO::setShift(std::string newShift)
{
    shift = newShift;
}

void ShiftDTO::setMaxLoad(int newMaxLoad)
{
    max_load = newMaxLoad;
}

void to_json(nlohmann::json& j, const ShiftDTO& shift)
{
	j = nlohmann::json
	{
		{"day", shift.getDay()},
		{"shift", shift.getShift()},
		{"max_load", shift.getMaxLoad()}
	};
}

void from_json(const nlohmann::json& j, ShiftDTO& shift)
{
	shift.setDay(j.at("day").get<int>());
	shift.setShift(j.at("shift").get<std::string>());
	shift.setMaxLoad(j.at("max_load").get<int>());

}
