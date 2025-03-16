#pragma once

#include "JSONOperations.h"

/**
 * @brief Facade for json nholman/json connector
*/
template <JsonConvertibleType T>
class JSONSerializableExchanger
{
public:
	JSONSerializableExchanger(const std::string& ip, short port);
	~JSONSerializableExchanger();

	void send(const T& toSend) override;

	void connectToPeer();

private:
	std::string _targetIP;
	short _targetPort;

	boost::asio::io_context io_context;
	boost::asio::ip::udp::socket socket;
	std::thread listenThread;
	bool _connected;

	void listenForResources();
};

template<JsonConvertibleType T>
inline JSONSerializableExchanger<T>::JSONSerializableExchanger(const std::string& ip, short port) :
    targetIP(ip),
    targetPort(port),
    socket(io_context),
    connected(false)
{}

template<JsonConvertibleType T>
inline JSONSerializableExchanger<T>::~JSONSerializableExchanger()
{
    if (connected)
    {
        socket.close();
        listenThread.join();
    }
}

template<JsonConvertibleType T>
inline void JSONSerializableExchanger<T>::send(const T& toSend)
{
    auto result = objectToJson<T>(toSend);

    boost::asio::write(socket, boost::asio::buffer(result));
}

template<JsonConvertibleType T>
inline void JSONSerializableExchanger<T>::connectToPeer()
{
    try
    {
        boost::asio::ip::udp::resolver resolver(io_context);
        boost::asio::connect(socket, resolver.resolve(targetIP, std::to_string(targetPort)));

        connected = true;

        listenThread = std::thread(&JSONSerializableExchanger::listenForResources, this);
    }
    catch (const std::exception& e)
    {
    }
}

template<JsonConvertibleType T>
inline void JSONSerializableExchanger<T>::listenForResources()
{
    try
    {
        while (connected)
        {
            char buffer[1024];
            size_t length = socket.receive(boost::asio::buffer(buffer));
            std::string message(buffer, length);

            std::cout << "Received: " << message << "\n";
        }
    }
    catch (...) {
        std::cerr << "Connection lost!\n";
        connected = false;
    }
}