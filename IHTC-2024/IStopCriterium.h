#pragma once

class IStopCriterium
{
public:
	IStopCriterium() = default;

	virtual ~IStopCriterium() = default;

	virtual bool isStop(double currTemp, int iteration) const = 0;
};