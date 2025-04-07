#pragma once

#include <boost/asio.hpp>

#include "CObservable.h"
#include "constants.h"
#include "JSONOperations.h"
#include "CGameInfo.h"

/**
 * @brief Class used as a receiver for creating sessions of the game using peer to peer
 */
class CSessionReceiverPeerToPeer : public CObservable<CGameInfo>
{
public:
	CSessionReceiverPeerToPeer(boost::asio::io_context& context);
	~CSessionReceiverPeerToPeer();
	void checkForSessions();

	void stopChecking();

protected:
	std::atomic<bool> _broadcast;  /// Tell the object to keep boradcasting (until this flag is false).
	boost::asio::ip::udp::socket _socket;

	void startReceivingBroadcast();
	void receiveBroadcast();
};