#pragma once
#include <functional>

#include "Patient.h"
#include "RoomDTO.h"
#include "OccupantDTO.h"
#include "ProblemData.h"
#include "RoomInfo.h"
#include "ViolatedRestrictions.h"

/*
	macierz timeslot/pacjent
	poczatkowo bedzie jakas lista kiedy jaki pacjent przyjety (miedzy release day i opcjonalnym due date)
	potem bedzie heurystycznie sprawdzane, czy da siê go w ten dany dzien przypisac w odpowiedni dzien
 */

class IHTCProblem
{
public:
	IHTCProblem(ProblemData& problemData);


private:

	// double startingTemp, std::function<double(double, int)> coolingFn, std::function<double(const WeightsDTO&)> eval
	void preprocessPatientsToRooms();

	ProblemData& problemData;

	std::vector<std::vector<int>> patientsInRoom;
	std::vector<std::unordered_map<std::string, PatientRoomInfo>> roomInfos;

	static constexpr int UNOCCUPIABLE = -INT_MAX;
	static constexpr int ASSIGNABLE = -1;

};