#pragma once

#include <string>
#include <vector>

#include "NurseDTO.h"
#include "ProblemData.h"

class ShiftNurses
{
public:
	ShiftNurses(const ProblemData& problemDatas);
	ShiftNurses(const ShiftNurses& other) = default;

	std::vector<NurseDTO> getNursesByDayShiftOffset(int offset);

private:
	static std::vector<std::vector<NurseDTO>> processNurses(const ProblemData& problemDatas);

	std::vector<std::vector<NurseDTO>> shiftNurses;
};