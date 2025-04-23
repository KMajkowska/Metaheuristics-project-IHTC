#pragma once

#include <string>
#include <functional>

#include "CObservable.h"

/**
 * @brief Interface for different types of network exchangers
 */
class INetworkExchanger : public CObservable<std::string>
{
public:

	virtual ~INetworkExchanger() = default;

	virtual void start() = 0;

	virtual void sendMessage(std::string message) = 0;
	virtual void receiveMessage() = 0;

	virtual void tellEndOfTransmission() = 0;

	virtual void disconnect() = 0;

	void setOnEndTransmission(std::function<void()> callback);
	void setOnConnect(std::function<void()> callback);

protected:
	std::function<void()> _onEndTransmission;
	std::function<void()> _onConnect;
};
