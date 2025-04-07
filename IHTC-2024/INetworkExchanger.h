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

	virtual void sendMessage(const std::string& message) = 0;
	virtual void receiveMessage() = 0;

	virtual void tellEndOfTransmission() = 0;

	void setOnClose(std::function<void()> callback);
	void setOnConnect(std::function<void()> callback);

protected:
	std::function<void()> _onClose;
	std::function<void()> _onConnect;
};
