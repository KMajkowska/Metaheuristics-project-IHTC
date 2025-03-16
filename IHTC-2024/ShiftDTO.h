#pragma once

#include <string>
#include <nlohmann/json.hpp>

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