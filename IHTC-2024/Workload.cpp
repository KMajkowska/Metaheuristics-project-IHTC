#include "Workload.h"

Workload::Workload(const std::vector<int>& max) :
	_max(max),
	_current(std::vector<int>(max.size(), 0))
{}

Workload::Workload(const SurgeonDTO& surgeon)
	: Workload(surgeon.maxSurgeryTime())
{}

Workload::Workload(const OperatingTheaterDTO& ot) :
	Workload(ot.getAvailability())
{}

Workload::Workload(const NurseDTO& nurse, int days, const std::unordered_map<std::string, int> shiftNameToPos) :
	Workload(nurse.workloadConverted(days, shiftNameToPos))
{}

void Workload::setMax(std::vector<int>&& max)
{
	_max = std::move(max);
}

void Workload::setCurrent(std::vector<int>&& current)
{
	_current = std::move(current);
}

std::vector<int>& Workload::max()
{
	return _max;
}

std::vector<int>& Workload::current()
{
	return _current;
}
