#pragma once

#include "PatientDTO.h"

/**
 * @brief DTO class to sepearte json data from data used to solve our problem. "Real" occupant is pretty similar, but we are separating json logic from algorithm logic
*/
class OccupantDTO : public PatientDTO
{

public:
	std::string roomId() const;

	void setRoomId(const std::string& newRoomId);

private:
	std::string _roomId;
};

void to_json(nlohmann::json& j, const OccupantDTO& occupant);
void from_json(const nlohmann::json& j, OccupantDTO& occupant);