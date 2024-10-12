#include "SurgeonDTO.h"

std::string SurgeonDTO::getId() const
{
    return id;
}

std::vector<int> SurgeonDTO::getMaxSurgeryTime() const
{
    return max_surgery_time;
}

void SurgeonDTO::setId(std::string newId)
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