#include "NurseWorkload.h"

NurseWorkload::NurseWorkload(std::vector<int> actual, std::vector<int> max) :
	_actualWorkload(actual),
	_maximumWorkload(max)
{}

void NurseWorkload::setActualWorkload(std::vector<int> && actualWorkload)
{
	_actualWorkload = std::move(actualWorkload);
}

void NurseWorkload::setMaximumWorkload(std::vector<int>&& maximumWorkload)
{
	_maximumWorkload = std::move(maximumWorkload);
}

std::vector<int>& NurseWorkload::actualWorkload()
{
	return _actualWorkload;
}

std::vector<int>& NurseWorkload::maximumWorkload()
{
	return _maximumWorkload;
}
