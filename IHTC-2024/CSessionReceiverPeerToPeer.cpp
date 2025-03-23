#include "CSessionReceiverPeerToPeer.h"

CSessionReceiverPeerToPeer::CSessionReceiverPeerToPeer() :
	_socket(_ioContext, boost::asio::ip::udp::endpoint(boost::asio::ip::udp::v4(), SESSION_PEER_TO_PEER_PORT)),
	_broadcast(false)
{}

CSessionReceiverPeerToPeer::~CSessionReceiverPeerToPeer()
{
	stopChecking();
}

void CSessionReceiverPeerToPeer::startReceivingBroadcast()
{
	_broadcast = true;
	receiveBroadcast();
}

void CSessionReceiverPeerToPeer::receiveBroadcast()
{
	std::vector<char> receiveBuffer(65507);
	boost::asio::ip::udp::endpoint senderEndpoint;

	while (_broadcast)
	{
		size_t length = _socket.receive_from(boost::asio::buffer(receiveBuffer), senderEndpoint);
		std::string message(receiveBuffer.begin(), receiveBuffer.begin() + length);

		std::cout << message << std::endl;

		auto parsed { nlohmann::json::parse(message) };
		auto gameInfoOpt { jsonToObject<CGameInfo>(parsed) };

		if (gameInfoOpt)
		{
			notify(gameInfoOpt.value());
		}
	}
}

void CSessionReceiverPeerToPeer::checkForSessions()
{
	_receiverThread = std::thread(&CSessionReceiverPeerToPeer::startReceivingBroadcast, this);
}

void CSessionReceiverPeerToPeer::stopChecking()
{
	_broadcast = false;
	_ioContext.stop();

	if (_receiverThread.joinable()) 
	{
		_receiverThread.join();
	}
}
