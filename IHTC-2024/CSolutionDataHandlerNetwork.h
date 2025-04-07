#pragma once

#include "SolutionData.h"
#include "CSolutionHandler.h"
#include "JSONSerializableExchanger.h"

/**
 * @brief Class that automatically sends and recieves data through the exchanger.
 */
class CSolutionDataHandlerNetwork : public CSolutionHandler, public JSONSerializableExchanger<SolutionData>
{
public:
	CSolutionDataHandlerNetwork(std::shared_ptr<INetworkExchanger> exchanger);

	void consumeLocal(SolutionData solution) override;

protected:
	void consume(SolutionData consumable) override;

};