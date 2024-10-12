#pragma once

#include <string>
#include <vector>
#include <nlohmann/json.hpp>

class OperatingTheaterDTO
{
public:
	std::string getId() const;
	std::vector<int> getAvailability() const;
private:
	std::string id;
	std::vector<int> availability;
};

void to_json(nlohmann::json& j, const OperatingTheaterDTO& ot);