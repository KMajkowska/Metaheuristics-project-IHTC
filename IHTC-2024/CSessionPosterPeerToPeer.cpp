#include "CSessionPosterPeerToPeer.h"

CSessionPosterPeerToPeer::CSessionPosterPeerToPeer(const CGameInfo& gameInfo) :
	_socket(_ioContext),
	_gameInfo(gameInfo),
	_endpoint(boost::asio::ip::address_v4::broadcast(), SESSION_PEER_TO_PEER_PORT),
	_broadcast(false)
{
	_socket.open(boost::asio::ip::udp::v4());
	_socket.set_option(boost::asio::socket_base::broadcast(true));

	auto gameInfoJsonOpt { objectToJson<CGameInfo>(_gameInfo) };

	if (!gameInfoJsonOpt)
	{
		throw std::invalid_argument("Game info couldn't be posted");
	}

	_message = std::move(gameInfoJsonOpt.value()) + "\n";
}

CSessionPosterPeerToPeer::~CSessionPosterPeerToPeer()
{
	stopBroadcast();
}

void CSessionPosterPeerToPeer::postSession()
{
	_broadcast = true;
	broadcastSession();
}

void CSessionPosterPeerToPeer::broadcastSession()
{
	while (_broadcast)
	{
		std::cout << "POST" << std::endl;
		_socket.send_to(boost::asio::buffer(_message), _endpoint);
		std::this_thread::sleep_for(std::chrono::seconds(BROADCAST_SESSION_TIMEOUT));
	}
}

void CSessionPosterPeerToPeer::stopBroadcast()
{	
	_broadcast = false;
}
