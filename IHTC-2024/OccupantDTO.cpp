#include "OccupantDTO.h"

std::string OccupantDTO::getRoomId() const
{
    return room_id;
}

void to_json(nlohmann::json& j, const OccupantDTO& occupant)
{
	nlohmann::to_json(j, static_cast<PatientDTO>(occupant));

	j.update({ {"room_id", occupant.getRoomId()} });
}

