#pragma once

#include <string>
#include <nlohmann/json.hpp>

/**
 * @brief DTO class to sepearte json data from data used to solve our problem. "Real" shift is pretty similar, but we are separating json logic from algorithm logic
*/
class ShiftDTO
{
public:
	int day() const;
	std::string shift() const;
	int maxLoad() const;

	void setDay(int newDay);
	void setShift(const std::string& newShift);
	void setMaxLoad(int newMaxLoad);

private:
	int _day;
	std::string _shift;
	int _maxLoad;
};

void to_json(nlohmann::json& j, const ShiftDTO& shift);
void from_json(const nlohmann::json& j, ShiftDTO& shift);