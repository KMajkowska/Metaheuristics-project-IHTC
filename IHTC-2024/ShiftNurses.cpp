#include "ShiftNurses.h"

ShiftNurses::ShiftNurses(const ProblemData& problemData) :
	shiftNurses(processNurses(problemData))
{}

std::vector<NurseDTO> ShiftNurses::getNursesByDayShiftOffset(int offset)
{
	return shiftNurses.at(offset);
}

std::vector<std::vector<NurseDTO>> ShiftNurses::processNurses(const ProblemData& problemData)
{
	int days = problemData.days();
	const auto& shifts = problemData.shiftTypes();

	std::vector<std::vector<NurseDTO>> res;
	res.reserve(days * shifts.size());


	for (int i = 0; i < days * shifts.size(); ++i)
	{
		std::vector<NurseDTO> nurses;
		res.push_back(nurses);
	}

	for (const auto& nurse : problemData.nurses())
	{
		for (const auto& shift : nurse.workingShifts())
		{
			res[shift.day() * shifts.size() + problemData.getOffsetOfShiftTypes(shift.shift())].push_back(nurse);
		}
	}

	return res;
}
