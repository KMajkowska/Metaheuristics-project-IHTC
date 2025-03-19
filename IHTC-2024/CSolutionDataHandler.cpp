#include "CSolutionDataHandler.h"

CSolutionDataHandler::CSolutionDataHandler(std::shared_ptr<INetworkExchanger> exchanger) :
	JSONSerializableExchanger(exchanger)
{
	addObserver([this](SolutionData data)
		{
			send(std::move(data));
		});
}

void CSolutionDataHandler::consume(SolutionData consumable)
{
	notify(std::move(consumable));
}
