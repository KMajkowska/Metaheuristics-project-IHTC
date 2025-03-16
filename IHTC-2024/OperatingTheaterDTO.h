#pragma once

#include <string>
#include <vector>
#include <nlohmann/json.hpp>

/**
 * @brief DTO class to sepearte json data from data used to solve our problem. "Real" operating theater is pretty similar, but we are separating json logic from algorithm logic
*/
class OperatingTheaterDTO
{
public:
	std::string id() const;
	std::vector<int> getAvailability() const;

	void setId(const std::string& newId);
	void setAvailability(std::vector<int> newAvailabilty);

private:
	std::string _id;
	std::vector<int> _availability;
};

void to_json(nlohmann::json& j, const OperatingTheaterDTO& ot);
void from_json(const nlohmann::json& j, OperatingTheaterDTO& ot);