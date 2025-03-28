#pragma once

#include <vector>

#include "ISolver.h"
#include "ICIndividualConsumer.h"

/**
 * @brief Solver, deriving from more generic solver. Is used for the exact problem we use in this project - IHTC. 
*/
class IHTCSolver : public ISolver
{
public:
	IHTCSolver(const ProblemData& problemData, std::mt19937& randGenerator, ICIndividualConsumer& individualConsumer);
	virtual ~IHTCSolver() = default;

protected:
	std::vector<std::vector<int>> _patientsInRoom;
	RoomWithOccupancyRepresentation _roomInfos;
	ICIndividualConsumer& _consumer;

	static constexpr int UNOCCUPIABLE = -INT_MAX;
	static constexpr int ASSIGNABLE = -1;
	static constexpr int UNDESIRED = -2;

private:
	/**
	 * @brief creates a vector of vector, when the patient can be assing, is the patient is already in the room (occuping room, not assiging in this solution) and 
	 * if on the potential assigning day surgeon has time for our patient
	*/
	void preprocessPatientsToRooms();
};