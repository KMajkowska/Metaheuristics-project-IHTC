#pragma once

#include <vector>

#include "ISolver.h"
#include "Logger.h"

class IHTCSolver : public ISolver
{
public:
	IHTCSolver(const ProblemData& problemData, std::mt19937& randGenerator, Logger& logger);

	virtual std::string getCSVHeaders() const = 0;

protected:
	std::vector<std::vector<int>> patientsInRoom;
	RoomWithOccupancyRepresentation roomInfos;
	Logger& logger;

	static constexpr int UNOCCUPIABLE = -INT_MAX;
	static constexpr int ASSIGNABLE = -1;
	static constexpr int UNDESIRED = -2;

private:
	void preprocessPatientsToRooms();
};