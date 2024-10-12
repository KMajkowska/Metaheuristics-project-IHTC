#include "OperatingTheaterDTO.h"

std::string OperatingTheaterDTO::getId() const
{
    return id;
}

std::vector<int> OperatingTheaterDTO::getAvailability() const
{
    return availability;
}

void OperatingTheaterDTO::setId(std::string newId)
{
    id = newId;
}

void OperatingTheaterDTO::setAvailability(std::vector<int> newAvailabilty)
{
    availability = newAvailabilty;
}

void to_json(nlohmann::json& j, const OperatingTheaterDTO& ot)
{
	j = nlohmann::json
	{
		{"id", ot.getId()},
		{"availability", ot.getAvailability()}
	};
}

void from_json(const nlohmann::json& j, OperatingTheaterDTO& ot)
{
	ot.setId(j.at("id").get<std::string>());
	ot.setAvailability(j.at("availability").get<std::vector<int>>());
}