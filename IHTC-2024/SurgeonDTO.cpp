#include "SurgeonDTO.h"

std::string SurgeonDTO::getId() const
{
    return id;
}

std::vector<int> SurgeonDTO::getMaxSurgeryTime() const
{
    return max_surgery_time;
}

void SurgeonDTO::setId(const std::string& newId)
{
    id = newId;
}

void SurgeonDTO::setMaxSurgeryTime(std::vector<int> newMaxSurgeryTime)
{
    max_surgery_time = newMaxSurgeryTime;
}

void to_json(nlohmann::json& j, const SurgeonDTO& surgeon)
{
	j = nlohmann::json
	{
		{"id", surgeon.getId()},
		{"max_surgery_time", surgeon.getMaxSurgeryTime()}
	};
}

void from_json(const nlohmann::json& j, SurgeonDTO& surgeon)
{
	surgeon.setId(j.at("id").get<std::string>());
	surgeon.setMaxSurgeryTime(j.at("max_surgery_time").get<std::vector<int>>());
}