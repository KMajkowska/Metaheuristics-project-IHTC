#pragma once

#include <iostream>
#include <thread>
#include <chrono>
#include <boost/asio.hpp>

#include "INetworkExchanger.h"

static std::string END_OF_TRANSMISSION = "EOT";

/**
 * @brief Allow connection of two computers in the same NAT/LAN
 */
class PeerToPeer : public INetworkExchanger
{
public:
	PeerToPeer(boost::asio::io_context& context, const std::string& ip, short sendPort, short receivePort, bool isHost);

	/**
	 * @brief Start the process of receiving messages and allow sending (establishes connection)
	 */
	void start() override;

	void sendMessage(const std::string& message) override;
	void receiveMessage() override;

	void tellEndOfTransmission() override;

private:
	boost::asio::ip::tcp::socket _sendSocket;
	boost::asio::ip::tcp::socket _receiveSocket;
	boost::asio::ip::tcp::acceptor _acceptor;

	boost::asio::streambuf _receiveBuffer;

	bool _connected;
	const std::string _ip;
	const short _sendPort;
	const short _receivePort;

	bool _isHost;

	void listenForConnections();
	void tryConnect();
};
