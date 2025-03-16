#pragma once

#include "PatientDTO.h"

class OccupantDTO : public PatientDTO
{

public:
	std::string roomId() const;

	void setRoomId(const std::string& newRoomId);

private:
	std::string room_id;
};

void to_json(nlohmann::json& j, const OccupantDTO& occupant);
void from_json(const nlohmann::json& j, OccupantDTO& occupant);