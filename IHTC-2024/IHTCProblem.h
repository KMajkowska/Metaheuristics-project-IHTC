#pragma once

#include "Patient.h"
#include "RoomDTO.h"
#include "OccupantDTO.h"
#include "ProblemData.h"
#include "RoomInfo.h"
#include "ViolatedRestrictions.h"
#include "CIndividual.h"
#include "IProblem.h"
#include "IHTCProblemIO.h"
#include "solutionUtils.h"

/*
	macierz timeslot/pacjent
	poczatkowo bedzie jakas lista kiedy jaki pacjent przyjety (miedzy release day i opcjonalnym due date)
	potem bedzie heurystycznie sprawdzane, czy da siê go w ten dany dzien przypisac w odpowiedni dzien
 */

class IHTCProblem : public IProblem
{
public:
	IHTCProblem(ProblemData& problemData, const std::function<double(const WeightsDTO&, const ViolatedRestrictions&)>& evalFn);

	virtual CIndividual solve() const = 0;

	double eval(const CIndividual& individual) const;

protected:
	ProblemData& problemData;

	std::vector<std::vector<int>> patientsInRoom;
	std::vector<std::unordered_map<std::string, PatientRoomInfo>> roomInfos;

	const std::function<double(const WeightsDTO&, const ViolatedRestrictions&)>& evalFn;

	static constexpr int UNOCCUPIABLE = -INT_MAX;
	static constexpr int ASSIGNABLE = -1;
	static constexpr int UNDESIRED = -2;

private: 
	void preprocessPatientsToRooms();

};