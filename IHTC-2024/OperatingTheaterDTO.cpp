#include "OperatingTheaterDTO.h"

std::string OperatingTheaterDTO::id() const
{
    return _id;
}

std::vector<int> OperatingTheaterDTO::getAvailability() const
{
    return _availability;
}

void OperatingTheaterDTO::setId(const std::string& newId)
{
    _id = newId;
}

void OperatingTheaterDTO::setAvailability(std::vector<int> newAvailabilty)
{
    _availability = newAvailabilty;
}

void to_json(nlohmann::json& j, const OperatingTheaterDTO& ot)
{
	j = nlohmann::json
	{
		{"id", ot.id()},
		{"availability", ot.getAvailability()}
	};
}

void from_json(const nlohmann::json& j, OperatingTheaterDTO& ot)
{
	ot.setId(j.at("id").get<std::string>());
	ot.setAvailability(j.at("availability").get<std::vector<int>>());
}