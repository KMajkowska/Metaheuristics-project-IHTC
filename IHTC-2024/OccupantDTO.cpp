#include "OccupantDTO.h"

std::string OccupantDTO::roomId() const
{
    return room_id;
}

void OccupantDTO::setRoomId(const std::string& newRoomId)
{
    room_id = newRoomId;
}

void to_json(nlohmann::json& j, const OccupantDTO& occupant)
{
	nlohmann::to_json(j, static_cast<PatientDTO>(occupant));

	j.update({ {"room_id", occupant.roomId()} });
}

void from_json(const nlohmann::json& j, OccupantDTO& occupant)
{
	nlohmann::from_json(j, static_cast<PatientDTO&>(occupant));

	occupant.setRoomId(j.at("room_id").get<std::string>());
}
