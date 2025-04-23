#include "INetworkExchanger.h"

void INetworkExchanger::setOnEndTransmission(std::function<void()> callback)
{
	_onEndTransmission = callback;
}

void INetworkExchanger::setOnConnect(std::function<void()> callback)
{
	_onConnect = callback;
}
