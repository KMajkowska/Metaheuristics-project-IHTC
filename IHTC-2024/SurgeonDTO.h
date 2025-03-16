#pragma once

#include <string>
#include <vector>
#include <nlohmann/json.hpp>

class SurgeonDTO
{
public:
	std::string id() const;
	std::vector<int> maxSurgeryTime() const;

	void setId(const std::string& newId);
	void setMaxSurgeryTime(std::vector<int> newMaxSurgeryTime);

private:
	std::string _id;
	std::vector<int> _maxSurgeryTime;
};

void to_json(nlohmann::json& j, const SurgeonDTO& surgeon);
void from_json(const nlohmann::json& j, SurgeonDTO& surgeon);