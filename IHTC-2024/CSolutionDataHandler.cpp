#include "CSolutionDataHandlerNetwork.h"

CSolutionDataHandlerNetwork::CSolutionDataHandlerNetwork(std::shared_ptr<INetworkExchanger> exchanger) :
	JSONSerializableExchanger(exchanger)
{}

void CSolutionDataHandlerNetwork::consumeLocal(SolutionData solution)
{
	send(solution);
	CSolutionHandler::consumeLocal(solution);
}

void CSolutionDataHandlerNetwork::consume(SolutionData consumable)
{
	consumeOpponent(std::move(consumable));
}
