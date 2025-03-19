#pragma once

#include <boost/asio.hpp>

#include "JSONOperations.h"
#include "INetworkExchanger.h"

/**
 * @brief Facade for network exchanger to send data converted to json.  
*/
template <JsonConvertibleType T>
class JSONSerializableExchanger
{
public:
	JSONSerializableExchanger(std::shared_ptr<INetworkExchanger> exchanger);

	void send(T toSend);

protected:

	/**
	 * @brief Cosumes data by sending it through the network using a network exchanger
	 * @param consumable Data to be consumed
	 */
	virtual void consume(T consumable) = 0;

private:
	std::shared_ptr<INetworkExchanger> _exchanger;
};

template<JsonConvertibleType T>
inline JSONSerializableExchanger<T>::JSONSerializableExchanger(std::shared_ptr<INetworkExchanger> exchanger) :
	_exchanger(exchanger)
{
	_exchanger->addObserver([this](std::string recieved)
		{
			auto parsed { nlohmann::json::parse(recieved) };
			std::optional<T> result{ jsonToObject<T>(parsed) };

			if (result)
			{
				consume(std::move(result.value()));
			}
		});
}

template<JsonConvertibleType T>
inline void JSONSerializableExchanger<T>::send(T toSend)
{
	std::optional<std::string> result { objectToJson<T>(toSend) };

	if (result)
	{
		_exchanger->sendMessage(std::move(result.value()));
	}
}