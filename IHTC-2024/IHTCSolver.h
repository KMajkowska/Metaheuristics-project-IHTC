#pragma once

#include <vector>

#include "ISolver.h"

class IHTCSolver : public ISolver
{
public:
	IHTCSolver(const ProblemData& problemData, std::mt19937& randGenerator);

protected:
	std::vector<std::vector<int>> patientsInRoom;
	RoomWithOccupancyRepresentation roomInfos;

	static constexpr int UNOCCUPIABLE = -INT_MAX;
	static constexpr int ASSIGNABLE = -1;
	static constexpr int UNDESIRED = -2;

private:
	void preprocessPatientsToRooms();
};