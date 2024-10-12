#pragma once
#include "PatientDTO.h"

class OccupantDTO : public PatientDTO
{

public:
	std::string getRoomId() const;

	void setRoomId(std::string newRoomId);

private:
	std::string room_id;
};