#pragma once

#include <string>
#include <vector>

#include "NurseDTO.h"
#include "ProblemData.h"

/**
 * @brief EVery nurse is on given day and on given shift. There we count and return the nurse whose is on provided day and shift.
*/
class ShiftNurses
{
public:
	ShiftNurses(const ProblemData& problemDatas);
	ShiftNurses(const ShiftNurses& other) = default;

	/**
	 * @brief 
	 * @param offset the offset, counted as problemData.getDays() * problemData.getShiftTypes().size() (days multiplied by number of shifts)
	 * @return vector of nurses on given day and shift
	*/
	std::vector<NurseDTO> getNursesByDayShiftOffset(int offset);

private:
	static std::vector<std::vector<NurseDTO>> processNurses(const ProblemData& problemDatas);

	std::vector<std::vector<NurseDTO>> _shiftNurses;
};