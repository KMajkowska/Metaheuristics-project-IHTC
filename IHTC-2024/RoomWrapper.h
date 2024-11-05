#pragma once

#include "CIndividual.h"
#include "ProblemData.h"

struct RoomWrapper
{
public:
	RoomWrapper(const PatientRoomInfo& newRoom, const ProblemData& newProblemData, const std::string& roomId);

	int operator<=>(const RoomWrapper&) const;

	const PatientRoomInfo& room;
	std::string roomId;

private:
	const ProblemData& problemData;
};