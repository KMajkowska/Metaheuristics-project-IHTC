#include "INetworkExchanger.h"

void INetworkExchanger::setOnClose(std::function<void()> callback)
{
	_onClose = callback;
}

void INetworkExchanger::setOnConnect(std::function<void()> callback)
{
	_onConnect = callback;
}
