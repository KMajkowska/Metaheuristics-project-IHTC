#include "SurgeryTimeActualToMax.h"

SurgeryTimeActualToMax::SurgeryTimeActualToMax(const std::vector<int>& max) :
	max(max),
	current(std::vector<int>(max.size(), 0))
{}

SurgeryTimeActualToMax::SurgeryTimeActualToMax(const SurgeonDTO & surgeon)
	: SurgeryTimeActualToMax(surgeon.getMaxSurgeryTime())
{}

SurgeryTimeActualToMax::SurgeryTimeActualToMax(const OperatingTheaterDTO & ot) :
	SurgeryTimeActualToMax(ot.getAvailability())
{
}
