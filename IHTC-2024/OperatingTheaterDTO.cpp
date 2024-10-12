#include "OperatingTheaterDTO.h"

std::string OperatingTheaterDTO::getId() const
{
    return id;
}

std::vector<int> OperatingTheaterDTO::getAvailability() const
{
    return availability;
}

void to_json(nlohmann::json& j, const OperatingTheaterDTO& ot)
{
	j = nlohmann::json
	{
		{"id", ot.getId()},
		{"availability", ot.getAvailability()}
	};
}
