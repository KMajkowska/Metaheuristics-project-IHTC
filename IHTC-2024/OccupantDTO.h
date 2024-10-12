#pragma once

#include "PatientDTO.h"

class OccupantDTO : public PatientDTO
{

public:
	std::string getRoomId() const;

private:
	std::string room_id;
};

void to_json(nlohmann::json& j, const OccupantDTO& occupant);