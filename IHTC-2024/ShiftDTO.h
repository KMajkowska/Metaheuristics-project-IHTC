#pragma once

#include <string>
#include <nlohmann/json.hpp>

class ShiftDTO
{
public:
	int getDay() const;
	std::string getShift() const;
	int getMaxLoad() const;

private:
	int day;
	std::string shift;
	int max_load;
};

void to_json(nlohmann::json& j, const ShiftDTO& shift);