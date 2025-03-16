#include "SurgeonDTO.h"

std::string SurgeonDTO::id() const
{
    return _id;
}

std::vector<int> SurgeonDTO::maxSurgeryTime() const
{
    return _maxSurgeryTime;
}

void SurgeonDTO::setId(const std::string& newId)
{
    _id = newId;
}

void SurgeonDTO::setMaxSurgeryTime(std::vector<int> newMaxSurgeryTime)
{
    _maxSurgeryTime = newMaxSurgeryTime;
}

void to_json(nlohmann::json& j, const SurgeonDTO& surgeon)
{
	j = nlohmann::json
	{
		{"id", surgeon.id()},
		{"max_surgery_time", surgeon.maxSurgeryTime()}
	};
}

void from_json(const nlohmann::json& j, SurgeonDTO& surgeon)
{
	surgeon.setId(j.at("id").get<std::string>());
	surgeon.setMaxSurgeryTime(j.at("max_surgery_time").get<std::vector<int>>());
}