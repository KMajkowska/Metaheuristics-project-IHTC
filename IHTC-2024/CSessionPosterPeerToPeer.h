#pragma once

#include <boost/asio.hpp>

#include "ISessionPoster.h"
#include "constants.h"
#include "JSONOperations.h"

/**
 * @brief Class used to post session through the peer to peer approach
 */
class CSessionPosterPeerToPeer : public ISessionPoster
{
public:
	CSessionPosterPeerToPeer(boost::asio::io_context& context, const CGameInfo& gameInfo);
	~CSessionPosterPeerToPeer();

	void postSession() override;
	void stopBroadcast();

private:
	const CGameInfo& _gameInfo;
	std::atomic<bool> _broadcast;  /// Tell the object to keep boradcasting (until this flag is false).
	std::string _message;
	boost::asio::io_context& _context;
	boost::asio::ip::udp::endpoint _endpoint;
	boost::asio::ip::udp::socket _socket;

	const short BROADCAST_SESSION_TIMEOUT = 2;

	void broadcastSession();
};