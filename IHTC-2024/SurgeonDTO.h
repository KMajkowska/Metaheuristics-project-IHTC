#pragma once

#include <string>
#include <vector>
#include <nlohmann/json.hpp>

class SurgeonDTO
{
public:
	std::string getId() const;
	std::vector<int> getMaxSurgeryTime() const;

	void setId(std::string newId);
	void setMaxSurgeryTime(std::vector<int> newMaxSurgeryTime);

private:
	std::string id;
	std::vector<int> max_surgery_time;
};

void to_json(nlohmann::json& j, const SurgeonDTO& surgeon);
void from_json(const nlohmann::json& j, const SurgeonDTO& surgeon);