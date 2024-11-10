#include "Workload.h"

Workload::Workload(const std::vector<int>& max) :
	max(max),
	current(std::vector<int>(max.size(), 0))
{}

Workload::Workload(const SurgeonDTO& surgeon)
	: Workload(surgeon.getMaxSurgeryTime())
{}

Workload::Workload(const OperatingTheaterDTO& ot) :
	Workload(ot.getAvailability())
{}

Workload::Workload(const NurseDTO& nurse, int days, const std::unordered_map<std::string, int> shiftNameToPos) :
	Workload(nurse.getWorkloadConverted(days, shiftNameToPos))
{}
