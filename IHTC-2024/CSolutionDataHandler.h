#pragma once

#include "SolutionData.h"
#include "JSONSerializableExchanger.h"
#include "ICObservable.h"

/**
 * @brief Class that automatically sends observed data through the exchanger.
 */
class CSolutionDataHandler : public JSONSerializableExchanger<SolutionData>, public ICObservable<SolutionData>
{
public:
	CSolutionDataHandler(std::shared_ptr<INetworkExchanger> exchanger);

	void consume(SolutionData consumable) override;

};