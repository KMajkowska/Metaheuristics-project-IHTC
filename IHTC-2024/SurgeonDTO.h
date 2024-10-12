#pragma once

#include <string>
#include <vector>
#include <nlohmann/json.hpp>

class SurgeonDTO
{
public:
	std::string getId() const;
	std::vector<int> getMaxSurgeryTime() const;
private:
	std::string id;
	std::vector<int> max_surgery_time;
};

void to_json(nlohmann::json& j, const SurgeonDTO& surgeon);
