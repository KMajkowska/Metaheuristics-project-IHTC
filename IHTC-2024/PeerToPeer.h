#pragma once

#include <deque>
#include <iostream>
#include <thread>
#include <chrono>
#include <boost/asio.hpp>

#include "INetworkExchanger.h"

static const std::string END_OF_TRANSMISSION{ "EOT" };
static const int MAX_RETRY_DELAY{ 2000 };
static const int MAX_ATTEMPTS{ 10 };

/**
 * @brief Allow connection of two computers in the same NAT/LAN
 */
class PeerToPeer : public INetworkExchanger
{
public:
	PeerToPeer(boost::asio::io_context&  ioContext, const std::string& ip, int port, bool isHost);
	~PeerToPeer();

	/**
	 * @brief Start the process of receiving messages and allow sending (establishes connection)
	 */
	void start() override;

	void sendMessage(std::string message) override;
	void receiveMessage() override;

	void disconnect() override;

	void tellEndOfTransmission() override;

private:
	boost::asio::ip::tcp::socket _socket;
	boost::asio::ip::tcp::acceptor _acceptor;

	boost::asio::streambuf _receiveBuffer;

	bool _connected;
	const std::string _ip;
	const int _port;

	bool _isHost;

	boost::asio::steady_timer _retryTimer;

	int _currentRetryDelay{ 100 };
	int _attemptCount{ 0 };

	void listenForConnections();
	void tryConnect();



	std::deque<std::string> _sendQueue;
	bool _writeInProgress = false;

	void onSuccesfullConnect();
};
