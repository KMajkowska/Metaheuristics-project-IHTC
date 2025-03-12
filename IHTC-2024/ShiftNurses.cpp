#include "ShiftNurses.h"

ShiftNurses::ShiftNurses(const ProblemData& problemData) :
	_shiftNurses(processNurses(problemData))
{}

std::vector<NurseDTO> ShiftNurses::getNursesByDayShiftOffset(int offset)
{
	return _shiftNurses.at(offset);
}

std::vector<std::vector<NurseDTO>> ShiftNurses::processNurses(const ProblemData& problemData)
{
	int days = problemData.getDays();
	const auto& shifts = problemData.getShiftTypes();

	std::vector<std::vector<NurseDTO>> res;
	res.reserve(days * shifts.size());


	for (int i = 0; i < days * shifts.size(); ++i)
	{
		std::vector<NurseDTO> nurses;
		res.push_back(nurses);
	}

	for (const auto& nurse : problemData.getNurses())
	{
		for (const auto& shift : nurse.getWorkingShifts())
		{
			res[shift.getDay() * shifts.size() + problemData.getOffsetOfShiftTypes(shift.getShift())].push_back(nurse);
		}
	}

	return res;
}
