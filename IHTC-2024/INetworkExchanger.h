#pragma once

#include <string>

#include "ICObservable.h"

/**
 * @brief Interface for different types of network exchangers
 */
class INetworkExchanger : public ICObservable<std::string>
{
public:

	virtual ~INetworkExchanger() = default;

	virtual void start() = 0;

	virtual void sendMessage(std::string message) = 0;
	virtual void receiveMessage() = 0;
};
