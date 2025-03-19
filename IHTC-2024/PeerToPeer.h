#pragma once

#include <boost/asio.hpp>
#include <iostream>
#include <thread>
#include <chrono>

#include "INetworkExchanger.h"

/**
 * @brief Allow connection of two computers in the same NAT/LAN
 */
class PeerToPeer : public INetworkExchanger
{
public:
	PeerToPeer(const std::string& ip, short sendPort, short receivePort);

	void start() override;

	void sendMessage(std::string message) override;
	void receiveMessage() override;

private:
	boost::asio::io_context _io_context;
	boost::asio::ip::tcp::socket _socket;
	boost::asio::ip::tcp::endpoint _endpoint;
	boost::asio::ip::tcp::acceptor _acceptor;
	boost::asio::executor_work_guard<boost::asio::io_context::executor_type> _work_guard;

	boost::asio::streambuf _receive_buffer;

	bool _connected;
	const std::string _ip;
	const int _sendPort;
	const int _receivePort;


	void listenForConnections();
	void tryConnect();
};
